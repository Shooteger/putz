#pragma once

#include <iostream>
#include <chrono>
#include <tuple>
#include <mutex>

class Clock {
    public:
        Clock(std::string name);
        Clock(std::string name_, int hours_, int minutes_, int seconds_);

        void operator()();
        void set_time(int hours, int minutes, int seconds);
        std::tuple<int, int, int> get_time();
        long to_time();
        void from_time(long time);

    private:
        std::string name;
        std::chrono::time_point<std::chrono::system_clock> curr_time;
};