#ifndef UNTITLED_GRAPH_H
#define UNTITLED_GRAPH_H

#include <vector>
#include <mutex>

namespace graph {

    class pair {
    public:
        int to;
        short weight;

        pair(int to, short weight) {
            this->to = to;
            this->weight = weight;
        }
    };


    class dijkstra {
    public:
        dijkstra() = default;

        std::vector<long long> operator()(
                std::vector<std::vector<graph::pair *>> &adj_list,
                int from
        );
    };


    class concurrent_dijkstra {
    public:
        concurrent_dijkstra() = default;

        long long *operator()(
                std::vector<std::vector<graph::pair *>> &adj_list,
                int from,
                int thread_count = 4
        );

    private:
        static std::mutex mutex;

        static void sub_job(
                long long *distances,
                char *used,
                char *queue,
                int iterations,
                int from,
                int to,
                int &min_index
        );
    };

}


#endif //UNTITLED_GRAPH_H
