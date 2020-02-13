#include "graph.hpp"

std::mutex graph::concurrent_dijkstra::mutex;

template<std::size_t SIZE>
std::array<long long, SIZE> graph::dijkstra::operator()(
        std::array<std::array<long long, SIZE>, SIZE> &weights,
        int from
) {
    std::array<long long, SIZE> distances;
    distances.fill(LONG_LONG_MAX);
    std::array<char, SIZE> queue = {};

    auto queue_size = 1;
    queue[from] = true;
    distances[from] = 0;

    while (queue_size != 0) {
        auto min_index = -1;

        for (auto i = 0; i < SIZE; ++i)
            if (queue[i] && (min_index == -1 || distances[i] < distances[min_index]))
                min_index = i;

        queue[min_index] = false;
        queue_size--;

        for (auto i = 0; i < SIZE; i++) {
            if (i == min_index || weights[min_index][i] < 1)
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
    std::array<long long, SIZE> distances;
    distances.fill(LONG_LONG_MAX);
    std::array<char, SIZE> queue = {};

    auto min_index = 0;
    std::atomic<int> flag {thread_count};
    queue[from] = true;
    distances[from] = 0;

    auto job_diff = SIZE / thread_count;
    auto job_remainder = SIZE % thread_count;
    auto last_start = 0;

    std::thread *threads[thread_count];
    for (int i = 0; i < thread_count; ++i) {
        auto remainder = i < job_remainder;
        *(threads + i) = new std::thread(
                [&weights, &distances, &queue, &min_index, &flag, thread_count, last_start, job_diff, remainder]() {
                    return sub_job(
                            weights,
                            distances,
                            queue,
                            flag,
                            min_index,
                            thread_count,
                            last_start,
                            last_start + job_diff + remainder
                    );
                }
        );
        last_start += job_diff + remainder;
    }
    for (auto thr : threads)
        if (thr->joinable())
            thr->join();
    return distances;
}

template<std::size_t SIZE>
void graph::concurrent_dijkstra::sub_job(
        std::array<std::array<long long, SIZE>, SIZE> &weights,
        std::array<long long, SIZE> &distances,
        std::array<char, SIZE> &queue,
        std::atomic<int> &flag,
        int &min_index,
        int thread_count,
        int from,
        int to
) {
    while (true) {
        auto local_min_index = -1;
        min_index = -1;
        for (auto i = from; i < to; i++)
            if (queue[i] && (local_min_index == -1 || distances[i] < distances[local_min_index]))
                local_min_index = i;

        if (local_min_index != -1) {
            mutex.lock();
            if (min_index == -1 || distances[min_index] > distances[local_min_index])
                min_index = local_min_index;
            mutex.unlock();
        }

        flag--;
        while (flag != 0);

        if (min_index == -1)
            return;
        if (local_min_index == min_index)
            queue[min_index] = false;
        flag = thread_count;

        for (auto i = from; i < to; i++) {
            if (i == min_index || weights[min_index][i] < 1)
                continue;

            if (distances[i] > distances[min_index] + weights[min_index][i]) {
                distances[i] = distances[min_index] + weights[min_index][i];
                if (!queue[i])
                    queue[i] = true;
            }
        }
    }
}
