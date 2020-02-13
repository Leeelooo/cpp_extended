#ifndef UNTITLED_UTILS_HPP
#define UNTITLED_UTILS_HPP

#include <functional>
#include <chrono>
#include <iostream>

namespace chrono {
    template<typename T>
    class time_block {
    public:
        time_block() = default;

        T operator()(std::function<T(void)> block) {
            auto start = std::chrono::system_clock::now();
            auto result = block();
            auto end = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now() - start);

            std::cout << end.count() << "ms" << std::endl;
            return result;
        }
    };
}

namespace ptr {
    template<typename T>
    class unique {
    public:
        unique() = default;

        explicit unique(T *data) : data(data) {}

        explicit unique(T &data) : data(&data) {}

        ~unique() {
            delete data;
        }

        T *operator->() const {
            return data;
        }

        T operator*() const {
            return *data;
        }

        unique<T> &operator=(unique<T> &&ptr) noexcept {
            if (this == ptr) return *this;
            data = std::move(ptr.data);
            ptr.data = nullptr;
            return *this;
        }
    private:
        T *data;
    };
}

#endif //UNTITLED_UTILS_HPP
