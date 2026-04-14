#ifndef ANALYZE_LOOPS_HPP
#define ANALYZE_LOOPS_HPP

#include <iostream>
#include <map>
#include <set>
#include <vector>

#include "cfg.hpp"
#include "dfs.hpp"

enum class LoopType { NONHEADER, SELF, REDUCIBLE, IRREDUCIBLE };

struct Loop {
    int id;
    int header_id;
    LoopType type;
    std::set<int> block_ids;
};

class AnalyzeLoops {
   public:
    AnalyzeLoops(CFG& cfg, DFS& dfs);

    void run();
    const std::vector<Loop>& getLoops() const;
    void printResults() const;

   private:
    CFG& cfg_;
    DFS& dfs_;
    std::vector<int> header_;
    std::vector<LoopType> type_;
    std::vector<Loop> loops_;

    void buildLoopNesting();
    void buildLoopsFromHeaders();
};

#endif