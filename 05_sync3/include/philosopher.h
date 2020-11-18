#pragma once

#include <iostream>
#include <mutex>
#include <thread>

class Philosopher {
    public:
        Philosopher(int new_id, std::mutex* right_f, std::mutex* left_f) : id{new_id}, right_fork{right_f}, left_fork{left_f} {};
        void operator()();
    private:
        std::mutex* left_fork;
        std::mutex* right_fork;
        int id;
};