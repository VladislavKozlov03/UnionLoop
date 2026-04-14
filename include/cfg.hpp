#ifndef CFG_HPP
#define CFG_HPP

#include <algorithm>
#include <cstddef>
#include <vector>

class BasicBlock {
   private:
    int id_;
    std::vector<int> succs_;
    std::vector<int> preds_;

   public:
    explicit BasicBlock(int id) : id_(id) {}

    int id() const { return id_; }

    const std::vector<int>& succs() const { return succs_; }
    std::vector<int>& succs() { return succs_; }

    const std::vector<int>& preds() const { return preds_; }
    std::vector<int>& preds() { return preds_; }

    void addSucc(int bb) { succs_.push_back(bb); }
    void addPred(int bb) { preds_.push_back(bb); }
};

class CFG {
   private:
    std::vector<BasicBlock> basic_blocks_;
    int startId = 0;
    int stopId = -1;

   public:
    void addBasicBlock();
    void addEdge(int from, int to);
    void removeEdge(int from, int to);

    void setStartId(int id) noexcept { startId = id; }
    void setStopId(int id) noexcept { stopId = id; }

    size_t size() const { return basic_blocks_.size(); }

    BasicBlock* getBlock(int id) {
        if (id < 0 || id >= static_cast<int>(basic_blocks_.size())) return nullptr;
        return &basic_blocks_[id];
    }

    const BasicBlock* getBlock(int id) const {
        if (id < 0 || id >= static_cast<int>(basic_blocks_.size())) return nullptr;
        return &basic_blocks_[id];
    }

    BasicBlock* getStart() { return getBlock(startId); }
    const BasicBlock* getStart() const { return getBlock(startId); }

    BasicBlock* getStop() { return getBlock(stopId); }
    const BasicBlock* getStop() const { return getBlock(stopId); }
};

#endif