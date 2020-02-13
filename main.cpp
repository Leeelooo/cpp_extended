#include <fstream>
#include "integral.cpp"
#include "matrix_utils.cpp"
#include "utils.hpp"

#define MATRIX_SIZE 600

// void test_graph() {
//     std::ifstream in("graph.txt");
//     int vertexes, edges;
//     in >> vertexes >> edges;
//
//     std::vector<std::vector<graph::pair *>> adj_list(vertexes, std::vector<graph::pair *>());
//
//     for (int i = 0; i < edges; ++i) {
//         int from, to;
//         short weight;
//         in >> from >> to >> weight;
//
//         if (from == to)
//             continue;
//
//         adj_list[from - 1].push_back(new graph::pair(to - 1, weight));
//     }
//
//     chrono::time_block<std::vector<long long>>()([&adj_list, vertexes]() {
//         return graph::dijkstra   ()(adj_list, 432);
//     });
//
//     chrono::time_block<std::vector<long long>>()([&adj_list, vertexes]() {
//         return graph::concurrent_dijkstra()(adj_list, 432, 2);
//     });
// }


void test_matrix() {
    std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> first;
    std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> second;

    for (auto i = 0; i < MATRIX_SIZE; ++i) {
        for (auto j = 0; j < MATRIX_SIZE; ++j) {
            first[i][j] = i;
            second[i][j] = j;
        }
    }

    chrono::time_block<std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> >()(
            [&first, &second]() {
                return matrix::multiplication()(first, second);
            }
    );

    chrono::time_block<std::array<std::array<int, MATRIX_SIZE>, MATRIX_SIZE> >()(
            [&first, &second]() {
                return matrix::concurrent_multiplication()(first, second, 4);
            }
    );
}

int main() {
    test_matrix();
    // test_graph();
}