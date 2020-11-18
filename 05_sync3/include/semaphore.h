#pragma once

#include <mutex>
#include <condition_variable>

class Semaphore {
    public:
        void aquire();
        void release();
        int available_permits();
    private:
        std::condition_variable not_empty;
        std::mutex mtx;
};