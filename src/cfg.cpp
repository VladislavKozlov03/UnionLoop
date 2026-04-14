#include "cfg.hpp"

#include <stdexcept>

void CFG::addBasicBlock() {
    const int id = static_cast<int>(basic_blocks_.size());
    basic_blocks_.emplace_back(id);
}

void CFG::addEdge(const int from, const int to) {
    if (from < 0 || from >= static_cast<int>(basic_blocks_.size()) || to < 0 ||
        to >= static_cast<int>(basic_blocks_.size()))
        throw std::out_of_range("CFG::addEdge: node id out of range");
    basic_blocks_[from].addSucc(to);
    basic_blocks_[to].addPred(from);
}

void CFG::removeEdge(const int from, const int to) {
    if (from < 0 || from >= static_cast<int>(basic_blocks_.size()) || to < 0 ||
        to >= static_cast<int>(basic_blocks_.size()))
        return;

    auto& succs = basic_blocks_[from].succs();
    auto& preds = basic_blocks_[to].preds();

    succs.erase(std::remove(succs.begin(), succs.end(), to), succs.end());
    preds.erase(std::remove(preds.begin(), preds.end(), from), preds.end());
}