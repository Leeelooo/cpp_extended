#ifndef UNTITLED_INTEGRAL_H
#define UNTITLED_INTEGRAL_H

#include <functional>
#include <mutex>

namespace _1D {
    template<typename T>
    class integral {
    public:
        integral() = default;

        double operator()(
                std::function<double(T)> func,
                double a,
                double b,
                long steps = 100
        );
    };

    template<typename T>
    class concurrent_integral {
    public:
        concurrent_integral() = default;

        double operator()(
                std::function<double(T)> func,
                double a,
                double b,
                long steps = 100,
                int thread_count = 4
        );

    private:

        static std::mutex mutex;

        static void sub_job(
                std::function<double(T)> func,
                double from,
                double to,
                double diff,
                double &result
        );
    };
}

#endif //UNTITLED_INTEGRAL_H
