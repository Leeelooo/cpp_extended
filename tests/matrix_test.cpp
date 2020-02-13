#include <array>
#include "gtest/gtest.h"
#include "matrix_utils.cpp"

class matrix_fixture : public ::testing::Test {

protected:
    void SetUp() override {
        multiplication = new matrix::multiplication();
        concurrent_multiplication = new matrix::concurrent_multiplication();
    }

    void TearDown() override {
        delete multiplication;
        delete concurrent_multiplication;
    }

    matrix::multiplication *multiplication;
    matrix::concurrent_multiplication *concurrent_multiplication;
};

TEST_F(matrix_fixture, multiplication_basic_correctness) {
    //2  3  4      3  1     114 10
    //1  0  7   *  32 0  =  24  15
    //9  -1 3      3  2     4   15
    //5  6  -2              201 1
    std::array<std::array<int, 3>, 4> first = {{
                                                       {2, 3, 4},
                                                       {1, 0, 7},
                                                       {9, -1, 3},
                                                       {5, 6, -2}
                                               }};
    std::array<std::array<int, 2>, 3> second = {{
                                                        {3, 1},
                                                        {32, 0},
                                                        {3, 2}
                                                }};
    std::array<std::array<int, 2>, 4> correct = {{
                                                         {114, 10},
                                                         {24, 15},
                                                         {4, 15},
                                                         {201, 1}
                                                 }};
    auto result = multiplication->operator()(first, second);
    ASSERT_TRUE(std::equal(result.cbegin(), result.cend(), correct.cbegin()));
}

TEST_F(matrix_fixture, concurrent_multiplication_basic_correctness) {
    //2  3  4      3  1     114 10
    //1  0  7   *  32 0  =  24  15
    //9  -1 3      3  2     4   15
    //5  6  -2              201 1
    std::array<std::array<int, 3>, 4> first = {{
                                                       {2, 3, 4},
                                                       {1, 0, 7},
                                                       {9, -1, 3},
                                                       {5, 6, -2}
                                               }};
    std::array<std::array<int, 2>, 3> second = {{
                                                        {3, 1},
                                                        {32, 0},
                                                        {3, 2}
                                                }};
    std::array<std::array<int, 2>, 4> correct = {{
                                                         {114, 10},
                                                         {24, 15},
                                                         {4, 15},
                                                         {201, 1}
                                                 }};
    auto result = concurrent_multiplication->operator()(first, second);
    ASSERT_TRUE(std::equal(result.cbegin(), result.cend(), correct.cbegin()));
}

TEST_F(matrix_fixture, concurrent_multiplication_not_equal_chunking) {
    //2  3  4      3  1     114 10
    //1  0  7   *  32 0  =  24  15
    //9  -1 3      3  2     4   15
    //5  6  -2              201 1
    std::array<std::array<int, 3>, 4> first = {{
                                                       {2, 3, 4},
                                                       {1, 0, 7},
                                                       {9, -1, 3},
                                                       {5, 6, -2}
                                               }};
    std::array<std::array<int, 2>, 3> second = {{
                                                        {3, 1},
                                                        {32, 0},
                                                        {3, 2}
                                                }};
    std::array<std::array<int, 2>, 4> correct = {{
                                                         {114, 10},
                                                         {24, 15},
                                                         {4, 15},
                                                         {201, 1}
                                                 }};
    auto result = concurrent_multiplication->operator()(first, second,3);
    ASSERT_TRUE(std::equal(result.cbegin(), result.cend(), correct.cbegin()));
}