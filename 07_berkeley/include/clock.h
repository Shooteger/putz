#pragma once

#include <iostream>
#include <chrono>

#include "timeutils.h"

class Clock {
    public:
        Clock(std::string name);
        Clock(std::string name_, int hours_, int minutes_, int secods_);

        void operator()();
        void set_time(int hours, int minutes, int secods);

    private:
        std::string name;
        std::chrono::time_point<std::chrono::system_clock> curr_time;
};