#ifndef UNTITLED_MATRIX_UTILS_H
#define UNTITLED_MATRIX_UTILS_H

#include <vector>

namespace matrix {
    template<typename T>
    class transpose {
    public:
        transpose() = default;

        std::vector<std::vector<T>> operator()(
                std::vector<std::vector<T>> matrix
        ) {
            std::vector<std::vector<T>> result(matrix[0].size(), std::vector<int>(matrix.size()));
            for (int i = 0; i < matrix.size(); ++i) {
                for (int j = 0; j < matrix[i].size(); ++j) {
                    result[j][i] = matrix[i][j];
                }
            }
            return result;
        }
    };

    template<typename T>
    class multiplication {
    public:
        multiplication() = default;

        T **operator()(
                std::vector<std::vector<T>> first,
                std::vector<std::vector<T>> second
        );
    };

    template<typename T>
    class concurrent_multiplication {
    public:
        concurrent_multiplication() = default;

        T **operator()(
                std::vector<std::vector<T>> first,
                std::vector<std::vector<T>> second,
                int thread_count = 4
        );

    private:
        static void sub_job(
                std::vector<std::vector<T>> first,
                std::vector<std::vector<T>> second,
                T **result,
                int from,
                int to
        );
    };
}

#endif //UNTITLED_MATRIX_UTILS_H
