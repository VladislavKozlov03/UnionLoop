#ifndef FIX_LOOPS_HPP
#define FIX_LOOPS_HPP

#include "cfg.hpp"
#include "dfs.hpp"

class FixLoops {
   public:
    FixLoops(CFG& cfg, DFS& dfs);
    int run();

   private:
    CFG& cfg_;
    DFS& dfs_;
};

#endif