#include <thread>
#include "matrix_utils.h"

template<typename T>
T **matrix::multiplication<T>::operator()(
        std::vector<std::vector<T>> first,
        std::vector<std::vector<T>> second
) {
    T **result = new T *[first.size()];
    for (int j = 0; j < first.size(); ++j) {
        *(result + j) = new T[second[0].size()];
    }

    for (int i = 0; i < first.size(); ++i) {
        for (int j = 0; j < second.at(0).size(); ++j) {
            for (int k = 0; k < second.size(); ++k) {
                *(*(result + i) + j) += first[i][k] * second[k][j];
            }
        }
    }
    return result;
}

template<typename T>
T **matrix::concurrent_multiplication<T>::operator()(
        std::vector<std::vector<T>> first,
        std::vector<std::vector<T>> second,
        int thread_count
) {
    T **result = new T *[first.size()];
    for (int j = 0; j < first.size(); ++j) {
        *(result + j) = new T[second[0].size()];
    }

    auto transposed_second = matrix::transpose<T>()(second);
    std::thread *threads[thread_count];
    auto iterations = first.size() / thread_count;
    for (int i = 0; i < thread_count; ++i) {
        *(threads + i) = new std::thread(
                matrix::concurrent_multiplication<T>::sub_job,
                first,
                transposed_second,
                result,
                i * iterations,
                (i + 1) * iterations
        );
    }

    for (auto thr : threads)
        if (thr->joinable())
            thr->join();

    return result;
}

template<typename T>
void matrix::concurrent_multiplication<T>::sub_job(
        std::vector<std::vector<T>> first,
        std::vector<std::vector<T>> second,
        T **result,
        int from,
        int to
) {
    for (int i = from; i < to; ++i) {
        for (int j = 0; j < second.size(); ++j) {
            for (int k = 0; k < second.size(); ++k) {
                *(*(result + i) + j) += first[i][k] * second[j][k];
            }
        }
    }
}