#ifndef UNTITLED_GRAPH_HPP
#define UNTITLED_GRAPH_HPP

#include <climits>
#include <vector>
#include <thread>
#include <array>
#include <mutex>
#include <atomic>

namespace graph {


    class dijkstra {
    public:
        dijkstra() = default;

        template<std::size_t SIZE>
        std::array<long long, SIZE> operator()(
                std::array<std::array<long long, SIZE>, SIZE> &weights,
                int from = 0
        );
    };


    class concurrent_dijkstra {
    public:
        concurrent_dijkstra() = default;

        template<std::size_t SIZE>
        std::array<long long, SIZE> operator()(
                std::array<std::array<long long, SIZE>, SIZE> &weights,
                int from = 0,
                int thread_count = 4
        );

    private:
        static std::mutex mutex;

        template<std::size_t SIZE>
        static void sub_job(
                std::array<std::array<long long, SIZE>, SIZE> &weights,
                std::array<long long, SIZE> &distances,
                std::array<char, SIZE> &queue,
                std::atomic<int> &flag,
                int &min_index,
                int thread_count,
                int from,
                int to
        );
    };

}


#endif //UNTITLED_GRAPH_HPP
