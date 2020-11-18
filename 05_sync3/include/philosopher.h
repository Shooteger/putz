#pragma once

#include <iostream>
#include <mutex>
#include <thread>

class Philosopher {
    public:
        Philosopher(int new_id, std::mutex* right_f, std::mutex* left_f) : left_fork{left_f}, right_fork{right_f}, id{new_id} {};
        void operator()();
    private:
        std::mutex* left_fork;
        std::mutex* right_fork;
        int id;
};