#include "analyze_loops.hpp"

#include <algorithm>

#include "union_find.hpp"

AnalyzeLoops::AnalyzeLoops(CFG& cfg, DFS& dfs) : cfg_(cfg), dfs_(dfs) {}

void AnalyzeLoops::run() {
    buildLoopNesting();
    buildLoopsFromHeaders();
}

const std::vector<Loop>& AnalyzeLoops::getLoops() const { return loops_; }

void AnalyzeLoops::printResults() const {
    std::cout << "Loop blocks:\n";
    for (const Loop& lp : loops_) {
        std::cout << "[" << lp.id << "] -> {";
        bool first = true;
        for (const int id : lp.block_ids) {
            if (!first) std::cout << ", ";
            std::cout << id;
            first = false;
        }
        std::cout << "}";
        if (lp.id != 0) {
            std::cout << ", header: " << lp.header_id << ", ";
            switch (lp.type) {
                case LoopType::REDUCIBLE:
                    std::cout << "reducible";
                    break;
                case LoopType::IRREDUCIBLE:
                    std::cout << "irreducible";
                    break;
                case LoopType::SELF:
                    std::cout << "self";
                    break;
                default:
                    std::cout << "nonheader";
                    break;
            }
        }
        std::cout << "\n";
    }

    std::cout << "Loop tree:\n";
    for (const Loop& lp : loops_) {
        if (lp.id == 0) continue;
        int parent_id = 0;
        for (const Loop& plp : loops_) {
            if (plp.id == lp.id) continue;
            if (plp.block_ids.count(lp.header_id) > 0) {
                parent_id = plp.id;
                break;
            }
        }
        std::cout << "{" << parent_id << "," << lp.id << "}\n";
    }
}

void AnalyzeLoops::buildLoopNesting() {
    BasicBlock* start = cfg_.getStart();
    if (!start) return;

    dfs_.run(&cfg_, start);
    const int N = dfs_.size();

    std::vector<std::vector<int>> backPreds(N + 1);
    std::vector<std::vector<int>> nonBackPreds(N + 1);
    header_.assign(N + 1, 1);
    type_.assign(N + 1, LoopType::NONHEADER);

    for (int w = 1; w <= N; ++w) {
        BasicBlock* blockW = dfs_.getNode(w);
        if (!blockW) continue;

        for (const int pred_id : blockW->preds()) {
            BasicBlock* v = cfg_.getBlock(pred_id);
            if (!v) continue;

            const int vNum = dfs_.getNumber(v);
            if (vNum == 0) continue;

            if (dfs_.isAncestor(w, vNum)) {
                backPreds[w].push_back(vNum);
            } else {
                nonBackPreds[w].push_back(vNum);
            }
        }
    }
    header_[1] = 0;

    UnionFind uf(N + 1);

    std::vector<bool> is_loop_header(N + 1, false);

    for (int w = N; w >= 1; --w) {
        std::vector<int> P;

        for (const int v : backPreds[w]) {
            if (v != w) {
                const int root = uf.find(v);
                if (std::find(P.begin(), P.end(), root) == P.end()) {
                    P.push_back(root);
                }
            } else {
                type_[w] = LoopType::SELF;
                is_loop_header[w] = true;
            }
        }

        if (!P.empty() && type_[w] != LoopType::SELF) {
            type_[w] = LoopType::REDUCIBLE;
            is_loop_header[w] = true;
        }

        std::vector<int> worklist = P;

        while (!worklist.empty()) {
            const int x = worklist.back();
            worklist.pop_back();

            for (const int y : nonBackPreds[x]) {
                const int yPrime = uf.find(y);

                if (!dfs_.isAncestor(w, yPrime)) {
                    type_[w] = LoopType::IRREDUCIBLE;
                    if (std::find(nonBackPreds[w].begin(), nonBackPreds[w].end(), yPrime) ==
                        nonBackPreds[w].end()) {
                        nonBackPreds[w].push_back(yPrime);
                    }
                } else {
                    if (yPrime != w && std::find(P.begin(), P.end(), yPrime) == P.end()) {
                        P.push_back(yPrime);
                        worklist.push_back(yPrime);
                    }
                }
            }
        }

        for (const int x : P) {
            if (header_[x] == 1) {
                header_[x] = w;
            }
            uf.unite(x, w);
        }

        if (is_loop_header[w]) {
            header_[w] = w;
        }
    }
}

void AnalyzeLoops::buildLoopsFromHeaders() {
    const int N = dfs_.size();

    std::set<int> all_headers;
    for (int i = 1; i <= N; ++i) {
        if (header_[i] == i) {
            all_headers.insert(i);
        }
    }

    std::set<int> valid_headers;
    for (const int h_pre : all_headers) {
        bool has_body = false;
        for (int i = 1; i <= N; ++i) {
            if (header_[i] == h_pre && i != h_pre) {
                has_body = true;
                break;
            }
        }
        if (has_body) {
            valid_headers.insert(h_pre);
        }
    }

    Loop root;
    root.id = 0;
    root.header_id = -1;
    root.type = LoopType::NONHEADER;
    loops_.push_back(root);

    int next_id = 1;
    std::map<int, int> header_pre_to_loop_id;
    for (const int h_pre : valid_headers) {
        Loop lp;
        lp.id = next_id++;
        lp.header_id = dfs_.getNode(h_pre)->id();
        lp.type = type_[h_pre];
        loops_.push_back(lp);
        header_pre_to_loop_id[h_pre] = lp.id;
    }

    for (int i = 1; i <= N; ++i) {
        const int h_pre = header_[i];
        BasicBlock* bb = dfs_.getNode(i);
        if (!bb) continue;

        if (h_pre == 0 || valid_headers.count(h_pre) == 0) {
            loops_[0].block_ids.insert(bb->id());
        } else {
            const int loop_id = header_pre_to_loop_id[h_pre];
            for (auto& lp : loops_) {
                if (lp.id == loop_id) {
                    lp.block_ids.insert(bb->id());
                    break;
                }
            }
        }
    }

    for (const int h_pre : valid_headers) {
        const int header_id = dfs_.getNode(h_pre)->id();
        loops_[0].block_ids.erase(header_id);
    }

    for (const int h_pre : valid_headers) {
        const int header_id = dfs_.getNode(h_pre)->id();
        const int loop_id = header_pre_to_loop_id[h_pre];
        for (auto& lp : loops_) {
            if (lp.id == loop_id) {
                lp.block_ids.insert(header_id);
                break;
            }
        }
    }
}