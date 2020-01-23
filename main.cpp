#include <vector>
#include <fstream>
#include "algo/matrix_utils.cpp"
#include "algo/integral.cpp"
#include "algo/graph.h"
#include "algo/utils.h"

#define INTEGRAL_STEPS 1000000000l
#define MATRIX_SIZE 1000

void test_graph() {
    std::ifstream in("graph.txt");
    int vertexes, edges;
    in >> vertexes >> edges;

    std::vector<std::vector<graph::pair *>> adj_list(vertexes, std::vector<graph::pair *>());

    for (int i = 0; i < edges; ++i) {
        int from, to;
        short weight;
        in >> from >> to >> weight;

        if (from == to)
            continue;

        adj_list[from - 1].push_back(new graph::pair(to - 1, weight));
    }

    chrono::time_block<std::vector<long long>>()([&adj_list, vertexes]() {
        return graph::dijkstra()(adj_list, 432);
    });

    chrono::time_block<std::vector<long long>>()([&adj_list, vertexes]() {
        return graph::concurrent_dijkstra()(adj_list, 432, 2);
    });
}

void test_integral() {
    chrono::time_block<double>()([]() {
        return _1D::integral<double>()(
                [](double x) { return x; },
                0,
                1,
                INTEGRAL_STEPS
        );
    });

    chrono::time_block<double>()([]() {
        return _1D::concurrent_integral<double>()(
                [](double x) { return x; },
                0,
                1,
                INTEGRAL_STEPS
        );
    });
}

void test_matrix() {
    auto first = std::vector(MATRIX_SIZE, std::vector(MATRIX_SIZE, 2));
    auto second = std::vector(MATRIX_SIZE, std::vector(MATRIX_SIZE, 6));

    chrono::time_block<int **>()([first, second]() {
        return matrix::multiplication<int>()(first, second);
    });

    chrono::time_block<int **>()([first, second]() {
        return matrix::concurrent_multiplication<int>()(first, second, 2);
    });
}

int main() {
//    test_integral();
//    test_matrix();
    test_graph();
}