#include "integral.hpp"

template<typename T>
std::mutex _1D::concurrent_integral<T>::mutex;

template<typename T>
double _1D::integral<T>::operator()(
        std::function<double(T)> func,
        double a,
        double b,
        long steps
) {
    double result_ = 0;
    double diff = (b - a) / steps;
    for (auto i = a; i < b; i += diff) {
        result_ += diff * (func(i) + func(i + diff)) / 2;
    }

    return result_;
}

template<typename T>
double _1D::concurrent_integral<T>::operator()(
        std::function<double(T)> func,
        double a,
        double b,
        long steps,
        int thread_count
) {
    double result = 0;

    auto diff = (b - a) / steps;
    auto job_diff = diff * (steps / thread_count);
    auto job_remainder = steps % thread_count;
    auto last_start = a;

    std::thread *threads[thread_count];
    for (int i = 0; i < thread_count; i++) {
        auto remainder = i < job_remainder ? diff : 0;
        *(threads + i) = new std::thread(
                [func, last_start, job_diff, remainder, diff, &result]() {
                    sub_job(
                            func,
                            last_start,
                            last_start + job_diff + remainder,
                            diff,
                            result
                    );
                });
        last_start += job_diff + remainder;
    }

    for (auto thr :threads)
        if (thr->joinable())
            thr->join();

    return result;
}

template<typename T>
void _1D::concurrent_integral<T>::sub_job(
        std::function<double(T)> func,
        double from,
        double to,
        double diff,
        double &result
) {
    double local_sum = 0;
    for (auto i = from; i < to; i += diff) {
        local_sum += diff * (func(i) + func(i + diff)) / 2;
    }
    std::lock_guard<std::mutex> lock(mutex);
    result += local_sum;
}