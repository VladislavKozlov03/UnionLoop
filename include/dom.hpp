#ifndef DOM_HPP
#define DOM_HPP

#include <set>
#include <unordered_map>
#include <vector>

#include "cfg.hpp"
#include "dfs.hpp"

using dom_tree_t = std::unordered_map<int, std::set<int>>;

inline dom_tree_t buildDominatorTree(CFG& cfg, DFS& dfs) {
    dom_tree_t dom_tree;

    BasicBlock* start = cfg.getStart();
    if (!start) return dom_tree;

    dfs.run(&cfg, start);
    const int N = dfs.size();

    std::vector<BasicBlock*> all_blocks;
    for (int i = 1; i <= N; ++i) {
        BasicBlock* bb = dfs.getNode(i);
        if (bb) all_blocks.push_back(bb);
    }

    for (BasicBlock* dom_bb : all_blocks) {
        dom_tree[dom_bb->id()] = std::set<int>();

        for (BasicBlock* target : all_blocks) {
            if (target == dom_bb) continue;

            std::set<int> visited;
            std::vector<BasicBlock*> stack;

            if (start != dom_bb) {
                stack.push_back(start);
                visited.insert(start->id());
            }

            while (!stack.empty()) {
                BasicBlock* curr = stack.back();
                stack.pop_back();

                for (const int succ_id : curr->succs()) {
                    BasicBlock* succ = cfg.getBlock(succ_id);
                    if (!succ) continue;
                    if (succ == dom_bb) continue;
                    if (visited.count(succ_id)) continue;

                    visited.insert(succ_id);
                    stack.push_back(succ);
                }
            }

            if (visited.count(target->id()) == 0) {
                dom_tree[dom_bb->id()].insert(target->id());
            }
        }
    }

    dfs.run(&cfg, start);
    return dom_tree;
}

inline bool dominates(const int a_id, const int b_id, const dom_tree_t& dom_tree) {
    if (a_id == b_id) return true;
    const auto it = dom_tree.find(a_id);
    if (it == dom_tree.end()) return false;
    return it->second.count(b_id) > 0;
}

#endif