#ifndef UNTITLED_MATRIX_UTILS_HPP
#define UNTITLED_MATRIX_UTILS_HPP

#include <array>
#include <thread>

namespace matrix {


    class transpose {
    public:
        transpose() = default;

        template <
                typename T,
                std::size_t R_SIZE,
                std::size_t C_SIZE
        >
        std::array<std::array<T, R_SIZE>, C_SIZE> operator()(
                std::array<std::array<T, C_SIZE>, R_SIZE> &matrix
        );
    };

    class multiplication {
    public:
        multiplication() = default;

        template <
                typename T,
                std::size_t FR_SIZE,
                std::size_t FC_SIZE,
                std::size_t SC_SIZE
        >
        std::array<std::array<T, FR_SIZE>, SC_SIZE> operator()(
                std::array<std::array<T, FC_SIZE>, FR_SIZE> &first,
                std::array<std::array<T, SC_SIZE>, FC_SIZE> &second
        );
    };


    class concurrent_multiplication {
    public:
        concurrent_multiplication() = default;

        template <
                typename T,
                std::size_t FR_SIZE,
                std::size_t FC_SIZE,
                std::size_t SC_SIZE
        >
        std::array<std::array<T, FR_SIZE>, SC_SIZE> operator()(
                std::array<std::array<T, FC_SIZE>, FR_SIZE> &first,
                std::array<std::array<T, SC_SIZE>, FC_SIZE> &second,
                int thread_count
        );

    private:
        template <
                typename T,
                std::size_t FR_SIZE,
                std::size_t FC_SIZE,
                std::size_t SC_SIZE
        >
        static void sub_job(
                std::array<std::array<T, FC_SIZE>, FR_SIZE> &first,
                std::array<std::array<T, SC_SIZE>, FC_SIZE> &second,
                std::array<std::array<T, FR_SIZE>, SC_SIZE> &result,
                int from,
                int to
        );
    };
}

#endif //UNTITLED_MATRIX_UTILS_HPP
