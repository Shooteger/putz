#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>

template <typename T>
class Pipe {
    public:
        Pipe& operator<<(T value) {
            if (!closed) {
                if (latency != 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(latency));
                }
                std::lock_guard<std::mutex> lg{mtx};
                backend.push(value);
                not_empty.notify_one();
            }
            return *this;
        }

        Pipe& operator>>(T& value) {
            if (!closed) {
                std::unique_lock<std::mutex> ul{mtx};
                not_empty.wait(ul, [&]() {return !closed && !backend.empty(); });
                value = backend.front();
                backend.pop();
            }
            return *this;
        }

        void close() {
            closed = true;
        }

        explicit operator bool() {
            return !closed;
        }

        void set_latency(long val) {
            latency = val;
        }
        
    private:
        std::queue<T> backend;
        std::mutex mtx;
        std::condition_variable not_empty;
        long latency;
        bool closed{false};
};