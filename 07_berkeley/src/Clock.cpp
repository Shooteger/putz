#include <iostream>
#include <chrono>

#include "clock.h"

using namespace std;

Clock::Clock(string name) {
    this->name = name;
    curr_time = chrono::system_clock::now();
}

