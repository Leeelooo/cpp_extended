#include <vector>
#include <climits>
#include <thread>
#include "graph.h"
#include "utils.h"

std::mutex graph::concurrent_dijkstra::mutex;

std::vector<long long> graph::dijkstra::operator()(
        std::vector<std::vector<graph::pair *>> &adj_list,
        int from
) {
    std::vector<long long> distances(adj_list.size(), LONG_LONG_MAX);
    std::vector<char> used(adj_list.size());
    std::vector<char> queue(adj_list.size());

    int queue_size = 1;
    queue[from] = true;
    distances[from] = 0;

    while (queue_size != 0) {
        int min_index = 0;
        for (int i = 1; i < adj_list.size(); ++i) {
            if (distances[i] < distances[min_index] && !used[i]) {
                min_index = i;
            }
        }

        used[min_index] = true;
        queue[min_index] = false;
        queue_size--;

        for (auto pair : adj_list[min_index]) {
            if (min_index == pair->to)
                continue;
            if (distances[pair->to] > distances[min_index] + pair->weight) {
                distances[pair->to] = distances[min_index] + pair->weight;
                if (!queue[pair->to]) {
                    queue[pair->to] = true;
                    queue_size++;
                }
            }
        }
    }
    return distances;
}

long long *graph::concurrent_dijkstra::operator()(
        std::vector<std::vector<graph::pair *>> &adj_list,
        int from,
        int thread_count
) {
    auto distances = array::make_array(adj_list.size(), LONG_LONG_MAX);
    auto used = array::make_array(adj_list.size(), 0);
    auto queue = array::make_array(adj_list.size(), 0);

    used.begin();

    int queue_size = 1;
    queue[from] = true;
    distances[from] = 0;

    int min_index = 0;
    std::thread *threads[thread_count];
    for (int i = 0; i < thread_count; ++i) {
        *(threads + i) = new std::thread(
                &graph::concurrent_dijkstra::sub_job,
                std::ref(distances),
                std::ref(used),
                i * (adj_list.size() / thread_count),
                (i + 1) * (adj_list.size() / thread_count) - 1,
                std::ref(min_index)
        );
    }
    for (auto thr : threads)
        if (thr->joinable())
            thr->join();

    while (queue_size != 0) {
        min_index = 0;

        used[min_index] = true;
        queue[min_index] = false;
        queue_size--;

        for (auto pair : adj_list[min_index]) {
            if (min_index == pair->to)
                continue;
            if (distances[pair->to] > distances[min_index] + pair->weight) {
                distances[pair->to] = distances[min_index] + pair->weight;
                if (!queue[pair->to]) {
                    queue[pair->to] = true;
                    queue_size++;
                }
            }
        }
    }
    return distances.begin();
}

void graph::concurrent_dijkstra::sub_job(
        long long *distances,
        char *used,
        char *queue,
        int iterations,
        int from,
        int to,
        int &min_index
) {
    for (int j = 0; j < iterations; ++j) {
        int local_min = -1;
        for (auto i = from; i < to; ++i) {
            if (*(used + i))
                continue;

            if (local_min == -1 || *(distances + i) < *(distances + local_min))
                local_min = i;
        }

        std::lock_guard<std::mutex> lock(mutex);
        if (distances[local_min] < distances[min_index])
            min_index = local_min;
    }
}