#include "gtest/gtest.h"
#include "integral.cpp"

#define INTEGRAL_STEPS 100000000l

class integral_fixture : public ::testing::Test {

protected:
    void SetUp() override {
        integral = new _1D::integral<double>();
        concurrent_integral = new _1D::concurrent_integral<double>();
    }

    void TearDown() override {
        delete integral;
        delete concurrent_integral;
    }

    _1D::integral<double> *integral;
    _1D::concurrent_integral<double> *concurrent_integral;
};

TEST_F(integral_fixture, check_equality) {
    auto result = integral->operator()(
            [](double x) { return 3 * x * x - 2 * x - 1 / x / x; },
            1,
            2,
            INTEGRAL_STEPS
    );
    auto result_concurrent = concurrent_integral->operator()(
            [](double x) { return 3 * x * x - 2 * x - 1 / x / x; },
            1,
            2,
            INTEGRAL_STEPS
    );
    EXPECT_EQ(result, result_concurrent);
    EXPECT_EQ(result, 3.5);
}