cmake_minimum_required(VERSION 3.14)
project(LoopAnalyzer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(loop_core STATIC
    src/cfg.cpp
    src/dfs.cpp
    src/analyze_loops.cpp
    src/fix_loops.cpp

)

add_executable(test_loops
    test/test_loops.cpp
    test/test_fixtures.cpp
)

target_link_libraries(test_loops PRIVATE loop_core GTest::gtest_main)