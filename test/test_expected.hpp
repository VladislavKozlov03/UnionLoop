#ifndef TEST_EXPECTED_HPP
#define TEST_EXPECTED_HPP

#include <set>
#include <string>
#include <unordered_map>
#include <vector>

struct Expected1 {
    static inline const std::unordered_map<int, std::set<int>> blocks = {{0, {0, 4, 5}},
                                                                         {1, {1, 2, 3}}};

    static inline const std::unordered_map<int, int> headers = {{1, 1}};

    static inline const std::unordered_map<int, std::string> types = {{1, "reducible"}};

    static inline const std::vector<std::pair<int, int>> nesting = {{0, 1}};
};

struct Expected2 {
    static inline const std::unordered_map<int, std::set<int>> blocks = {
        {0, {0, 5}}, {1, {2, 4}}, {2, {1, 3}}};

    static inline const std::unordered_map<int, int> headers = {{1, 2}, {2, 1}};

    static inline const std::unordered_map<int, std::string> types = {{1, "reducible"},
                                                                      {2, "reducible"}};

    static inline const std::vector<std::pair<int, int>> nesting = {{0, 1}, {0, 2}};
};

struct Expected3 {
    static inline const std::unordered_map<int, std::set<int>> blocks = {{0, {0, 1, 2, 3, 4, 5}}};

    static inline const std::unordered_map<int, int> headers = {};
    static inline const std::unordered_map<int, std::string> types = {};
    static inline const std::vector<std::pair<int, int>> nesting = {};
};

struct Expected4 {
    static inline const std::unordered_map<int, std::set<int>> blocks = {
        {0, {0, 1, 6, 7}}, {1, {2, 5}}, {2, {3, 4}}};

    static inline const std::unordered_map<int, int> headers = {};
    static inline const std::unordered_map<int, std::string> types = {};
    static inline const std::vector<std::pair<int, int>> nesting = {};
};

#endif