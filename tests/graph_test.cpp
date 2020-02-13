#include <array>
#include "gtest/gtest.h"
#include "graph.cpp"

class graph_fixture : public ::testing::Test {

protected:
    void SetUp() override {
        dijkstra = new graph::dijkstra();
        concurrent_dijkstra = new graph::concurrent_dijkstra();
    }

    void TearDown() override {
        delete dijkstra;
        delete concurrent_dijkstra;
    }

    graph::dijkstra *dijkstra;
    graph::concurrent_dijkstra *concurrent_dijkstra;
};

TEST_F(graph_fixture, dijkstra_correctness) {
    std::array<std::array<long long, 9>, 9> weights = {{
                                                         {0, 4, 0, 0, 0, 0, 0, 8, 0},
                                                         {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                                         {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                                         {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                                         {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                                         {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                                         {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                                         {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                                         {0, 0, 2, 0, 0, 0, 6, 7, 0}
                                                 }};
    std::array<long long, 9> answer = {0, 4, 12, 19, 21, 11, 9, 8, 14};
    auto result = dijkstra->operator()(weights);
    ASSERT_TRUE(std::equal(answer.cbegin(), answer.cend(), result.cbegin()));
}

TEST_F(graph_fixture, concurrent_dijkstra_correctness) {
    std::array<std::array<long long, 9>, 9> weights = {{
                                                               {0, 4, 0, 0, 0, 0, 0, 8, 0},
                                                               {4, 0, 8, 0, 0, 0, 0, 11, 0},
                                                               {0, 8, 0, 7, 0, 4, 0, 0, 2},
                                                               {0, 0, 7, 0, 9, 14, 0, 0, 0},
                                                               {0, 0, 0, 9, 0, 10, 0, 0, 0},
                                                               {0, 0, 4, 14, 10, 0, 2, 0, 0},
                                                               {0, 0, 0, 0, 0, 2, 0, 1, 6},
                                                               {8, 11, 0, 0, 0, 0, 1, 0, 7},
                                                               {0, 0, 2, 0, 0, 0, 6, 7, 0}
                                                       }};
    std::array<long long, 9> answer = {0, 4, 12, 19, 21, 11, 9, 8, 14};
    auto result = concurrent_dijkstra->operator()(weights);
    ASSERT_TRUE(std::equal(answer.cbegin(), answer.cend(), result.cbegin()));
}