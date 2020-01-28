#include "integral.h"

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
    for (double i = a; i < b; i += diff) {
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

    double diff = (b - a) / steps;
    double job_diff = diff * (steps / thread_count);

    std::thread *threads[thread_count];
    for (int i = 0; i < thread_count; i++) {
        *(threads + i) = new std::thread(
                _1D::concurrent_integral<T>::sub_job,
                func,
                a + i * job_diff,
                a + (i + 1) * job_diff,
                diff,
                std::ref(result)
        );
    }

    for (auto thr :threads) {
        if (thr->joinable())
            thr->join();
    }
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
    for (double i = from; i < to; i += diff) {
        local_sum += diff * (func(i) + func(i + diff)) / 2;
    }
    std::lock_guard<std::mutex> lock(mutex);
    result += local_sum;
}