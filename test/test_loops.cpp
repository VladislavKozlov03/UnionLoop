#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "analyze_loops.hpp"
#include "dfs.hpp"
#include "fix_loops.hpp"
#include "test_fixtures.hpp"

static void expect_eq_loop(const Loop& result, const Loop& expected) {
    EXPECT_EQ(result.id, expected.id);
    EXPECT_EQ(result.header_id, expected.header_id);
    EXPECT_EQ(result.type, expected.type);
    EXPECT_EQ(result.block_ids, expected.block_ids);
}

static void expect_eq_loops(std::vector<Loop> result, std::vector<Loop> expected) {
    ASSERT_EQ(result.size(), expected.size());

    auto sort_lambda = [](const Loop& lhs, const Loop& rhs) { return lhs.id < rhs.id; };

    std::sort(result.begin(), result.end(), sort_lambda);
    std::sort(expected.begin(), expected.end(), sort_lambda);

    for (size_t i = 0; i != result.size(); ++i) {
        expect_eq_loop(result[i], expected[i]);
    }
}

TEST_F(Graph1, AnalyzeLoops) {
    DFS dfs;
    FixLoops fix(graph, dfs);
    int inserted = fix.run();
    std::cout << "Graph1: inserted " << inserted << " blocks\n";

    AnalyzeLoops analyzer(graph, dfs);
    analyzer.run();

    std::cout << "\nGRAPH 1\n";
    analyzer.printResults();

    const auto& loops = analyzer.getLoops();

    std::vector<Loop> expected_loops{
        {.id = 0, .header_id = -1, .type = LoopType::NONHEADER, .block_ids = {0, 4, 5}},
        {.id = 1, .header_id = 1, .type = LoopType::REDUCIBLE, .block_ids = {1, 2, 3}}};

    expect_eq_loops(loops, expected_loops);
}

TEST_F(Graph2, AnalyzeLoops) {
    DFS dfs;
    FixLoops fix(graph, dfs);
    int inserted = fix.run();
    std::cout << "Graph2: inserted " << inserted << " blocks\n";

    AnalyzeLoops analyzer(graph, dfs);
    analyzer.run();

    std::cout << "\nGRAPH 2\n";
    analyzer.printResults();

    const auto& loops = analyzer.getLoops();

    std::vector<Loop> expected_loops{
        {.id = 0, .header_id = -1, .type = LoopType::NONHEADER, .block_ids = {0, 5}},
        {.id = 1, .header_id = 1, .type = LoopType::REDUCIBLE, .block_ids = {1, 3}},
        {.id = 2, .header_id = 2, .type = LoopType::REDUCIBLE, .block_ids = {2, 4}}};

    expect_eq_loops(loops, expected_loops);
}

TEST_F(Graph3, AnalyzeLoops) {
    DFS dfs;
    FixLoops fix(graph, dfs);
    int inserted = fix.run();
    std::cout << "Graph3: inserted " << inserted << " blocks\n";

    AnalyzeLoops analyzer(graph, dfs);
    analyzer.run();

    std::cout << "\nGRAPH 3\n";
    analyzer.printResults();

    const auto& loops = analyzer.getLoops();

    std::vector<Loop> expected_loops{
        {.id = 0, .header_id = -1, .type = LoopType::NONHEADER, .block_ids = {0, 1, 2, 3, 4, 5}}};

    expect_eq_loops(loops, expected_loops);
}

TEST_F(Graph4, AnalyzeLoops) {
    DFS dfs;
    FixLoops fix(graph, dfs);
    int inserted = fix.run();
    std::cout << "Graph4: inserted " << inserted << " blocks\n";

    AnalyzeLoops analyzer(graph, dfs);
    analyzer.run();

    std::cout << "\nGRAPH 4\n";
    analyzer.printResults();

    const auto& loops = analyzer.getLoops();

    std::vector<Loop> expected_loops{
        {.id = 0, .header_id = -1, .type = LoopType::NONHEADER, .block_ids = {0, 1, 6, 7}},
        {.id = 1, .header_id = 2, .type = LoopType::REDUCIBLE, .block_ids = {2, 5}},
        {.id = 2, .header_id = 3, .type = LoopType::REDUCIBLE, .block_ids = {3, 4}}};

    expect_eq_loops(loops, expected_loops);
}