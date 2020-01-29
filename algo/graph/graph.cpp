#include <vector>
#include <climits>
#include <thread>
#include "graph.hpp"

std::mutex graph::concurrent_dijkstra::mutex;

template<std::size_t SIZE>
std::array<long long, SIZE> graph::dijkstra::operator()(
        std::array<std::array<long long, SIZE>, SIZE> &weights,
        int from
) {
    auto distances = array::make_array(weight.size(), LLONG_MAX);
    auto used = array::make_array(weight.size(), 0);
    auto queue = array::make_array(weight.size(), 0);

    auto queue_size = 1;
    queue[from] = true;
    distances[from] = 0;

    while (queue_size != 0) {
        auto min_index = 0;
        while (used[min_index])
            min_index++;
        
        for (auto i = 1; i < weights.size(); ++i) 
            if (distances[i] < distances[min_index] && !used[i])
                min_index = i;

        used[min_index] = true;
        queue[min_index] = false;
        queue_size--;

        for (auto i = 0; i < weights[min_index].size(); i++) {
            if (i == min_index)
                continue;
            
            if (distances[i] > distances[min_index] + weights[min_index][i]) {
                distances[i] = distances[min_index] + weights[min_index][i];
                if (!queue[i]) {
                    queue[i] = true;
                    queue_size++;
                }
            }
        }
    }
    return distances;
}

template<std::size_t SIZE>
std::array<long long, SIZE> graph::concurrent_dijkstra::operator()(
        std::array<std::array<long long, SIZE>, SIZE> &weights,
        int from,
        int thread_count
) {
    auto distances = array::make_array(weight.size(), LLONG_MAX);
    auto used = array::make_array(weight.size(), 0);
    auto queue = array::make_array(weight.size(), 0);
    
    auto beg = distances.begin();
    

    auto queue_size = 1;
    queue[from] = true;
    distances[from] = 0;

    auto min_index = 0;
    std::thread *threads[thread_count];
    for (int i = 0; i < thread_count; ++i) {
        *(threads + i) = new std::thread(
                &graph::concurrent_dijkstra::sub_job,
                std::ref(distances),
                std::ref(used),
                i * (weights
    .size() / thread_count),
                (i + 1) * (weights
    .size() / thread_count) - 1,
                std::ref(min_index)
        );
    }
    for (auto thr : threads)
        if (thr->joinable())
            thr->join();
    return distances;
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