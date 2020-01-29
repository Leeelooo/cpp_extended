#ifndef UNTITLED_GRAPH_HPP
#define UNTITLED_GRAPH_HPP

#include <array>
#include <mutex>

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

        template<typename ITER_DIS, typename ITER_QUEUE>
        static void sub_job(
            ITER_DIS distances_begin,
            ITER_DIS distances_end,
            ITER_QUEUE queue_begin,
            ITER_QUEUE queue_end,
            ITER_QUEUE used_begin,
            ITER_QUEUE used_end,
            int &ref,
            int &next_queue_ready,
            int &queue_size_ref 
        );
    };

}


#endif //UNTITLED_GRAPH_HPP
