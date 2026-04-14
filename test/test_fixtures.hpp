#ifndef TEST_FIXTURES_HPP
#define TEST_FIXTURES_HPP

#include <gtest/gtest.h>

#include <vector>

#include "cfg.hpp"

class Graph1 : public ::testing::Test {
   protected:
    void SetUp() override;
    CFG graph;
};

class Graph2 : public ::testing::Test {
   protected:
    void SetUp() override;
    CFG graph;
};

class Graph3 : public ::testing::Test {
   protected:
    void SetUp() override;
    CFG graph;
};

class Graph4 : public ::testing::Test {
   protected:
    void SetUp() override;
    CFG graph;
};

#endif