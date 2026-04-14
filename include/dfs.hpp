#ifndef DFS_HPP
#define DFS_HPP

#include <unordered_map>
#include <vector>

#include "cfg.hpp"

class DFS {
   public:
    void run(CFG* cfg, BasicBlock* start);

    bool isAncestor(int w, int v) const;
    int getNumber(BasicBlock* bb) const;
    BasicBlock* getNode(int pre) const;
    int size() const { return static_cast<int>(node_.size()) - 1; }

   private:
    void dfs(BasicBlock* a);

    CFG* cfg_ = nullptr;
    int current_ = 1;
    std::unordered_map<BasicBlock*, int> number_;
    std::vector<BasicBlock*> node_;
    std::vector<int> last_;
};

#endif