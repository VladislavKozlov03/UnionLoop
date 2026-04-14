#include "fix_loops.hpp"

#include <vector>

#include "dom.hpp"

FixLoops::FixLoops(CFG& cfg, DFS& dfs) : cfg_(cfg), dfs_(dfs) {}

int FixLoops::run() {
    BasicBlock* start = cfg_.getStart();
    if (!start) return 0;

    dfs_.run(&cfg_, start);
    const int N = dfs_.size();

    const dom_tree_t dom = buildDominatorTree(cfg_, dfs_);

    struct NodeInfo {
        int w_id;
        std::vector<int> redBackIn;
        std::vector<int> otherIn;
    };

    std::vector<NodeInfo> infos;
    infos.reserve(N);

    for (int pre = 1; pre <= N; ++pre) {
        BasicBlock* w = dfs_.getNode(pre);
        if (!w) continue;

        NodeInfo info;
        info.w_id = w->id();

        for (const int v_id : w->preds()) {
            if (dominates(w->id(), v_id, dom))
                info.redBackIn.push_back(v_id);
            else
                info.otherIn.push_back(v_id);
        }

        if (!info.redBackIn.empty() && info.otherIn.size() > 1) infos.push_back(std::move(info));
    }

    if (infos.empty()) return 0;

    for (const auto& info : infos) {
        cfg_.addBasicBlock();
        const int wprime_id = static_cast<int>(cfg_.size()) - 1;

        cfg_.addEdge(wprime_id, info.w_id);

        for (const int v_id : info.otherIn) {
            cfg_.removeEdge(v_id, info.w_id);
            cfg_.addEdge(v_id, wprime_id);
        }
    }

    dfs_.run(&cfg_, cfg_.getStart());
    return static_cast<int>(infos.size());
}