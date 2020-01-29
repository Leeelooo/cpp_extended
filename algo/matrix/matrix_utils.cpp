#include "matrix_utils.hpp"

template <
        typename T,
        std::size_t R_SIZE,
        std::size_t C_SIZE
>
std::array<std::array<T, R_SIZE>, C_SIZE>
matrix::transpose::operator()(
        std::array<std::array<T,C_SIZE>,R_SIZE> &matrix
) {
    std::array<std::array<T, R_SIZE>, C_SIZE> result;
    for (auto i = 0; i < R_SIZE; ++i)
        for (auto j = 0; j < C_SIZE; ++j)
            result[j][i] = matrix[i][j];

    return result;
}


template<
        typename T,
        std::size_t FR_SIZE,
        std::size_t FC_SIZE,
        std::size_t SC_SIZE
>
std::array<std::array<T, FR_SIZE>, SC_SIZE>
matrix::multiplication::operator()(
        std::array<std::array<T, FC_SIZE>, FR_SIZE> &first,
        std::array<std::array<T, SC_SIZE>, FC_SIZE> &second
) {
    std::array<std::array<T, FR_SIZE>, SC_SIZE> result = {};

    for (auto i = 0; i < FR_SIZE; ++i)
        for (auto j = 0; j < SC_SIZE; ++j)
            for (auto k = 0; k < FC_SIZE; ++k)
                result[i][j] += first[i][k] * second[k][j];

    return result;
}


template <
        typename T,
        std::size_t FR_SIZE,
        std::size_t FC_SIZE,
        std::size_t SC_SIZE
>
std::array<std::array<T, FR_SIZE>, SC_SIZE>
matrix::concurrent_multiplication::operator()(
        std::array<std::array<T, FC_SIZE>, FR_SIZE> &first,
        std::array<std::array<T, SC_SIZE>, FC_SIZE> &second,
        int thread_count
) {
    std::array<std::array<T, FR_SIZE>, SC_SIZE> result = {};

    auto transposed_second = matrix::transpose()(second);
    std::thread *threads[thread_count];
    auto iterations = first.size() / thread_count;
    for (auto i = 0; i < thread_count; ++i) {
        *(threads + i) = new std::thread(
                [&first, &second, &result, i, iterations]() {
                    sub_job(first, second, result, i * iterations, (i + 1) * iterations);
                }
        );
    }

    for (auto thr : threads)
        if (thr->joinable())
            thr->join();

    return result;
}

template <
        typename T,
        std::size_t FR_SIZE,
        std::size_t FC_SIZE,
        std::size_t SC_SIZE
>
void matrix::concurrent_multiplication::sub_job(
        std::array<std::array<T, FC_SIZE>, FR_SIZE> &first,
        std::array<std::array<T, SC_SIZE>, FC_SIZE> &second,
        std::array<std::array<T, FR_SIZE>, SC_SIZE> &result,
        int from,
        int to
){
    for (auto i = from; i < to; ++i)
        for (auto j = 0; j < SC_SIZE; ++j)
            for (auto k = 0; k < FC_SIZE; ++k)
                result[i][j] += first[i][k] * second[k][j   ];
}