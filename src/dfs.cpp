#include "dfs.hpp"

void DFS::run(CFG* cfg, BasicBlock* start) {
    cfg_ = cfg;
    number_.clear();
    node_.clear();
    last_.clear();

    node_.push_back(nullptr);
    last_.push_back(0);
    current_ = 1;

    if (start) {
        dfs(start);
    }
}

void DFS::dfs(BasicBlock* a) {
    if (static_cast<int>(node_.size()) <= current_) {
        node_.resize(current_ + 1);
        last_.resize(current_ + 1);
    }
    node_[current_] = a;

    const int myNumber = current_;
    number_[a] = myNumber;
    ++current_;

    for (const int succ_id : a->succs()) {
        BasicBlock* b = cfg_->getBlock(succ_id);
        if (b && getNumber(b) == 0) {
            dfs(b);
        }
    }

    last_[myNumber] = current_ - 1;
}

bool DFS::isAncestor(const int w, const int v) const {
    if (w <= 0 || v <= 0 || w >= static_cast<int>(last_.size()) ||
        v >= static_cast<int>(last_.size()))
        return false;
    return (w <= v) && (v <= last_[w]);
}

int DFS::getNumber(BasicBlock* bb) const {
    const auto it = number_.find(bb);
    return (it != number_.end()) ? it->second : 0;
}

BasicBlock* DFS::getNode(const int pre) const {
    if (pre > 0 && pre < static_cast<int>(node_.size())) return node_[pre];
    return nullptr;
}