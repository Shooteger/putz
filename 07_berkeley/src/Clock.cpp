#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>

#include "clock.h"
#include "timeutils.h"

using namespace std;

mutex mtx;

Clock::Clock(string name) {
    this->name = name;
    curr_time = chrono::system_clock::now();
}

void Clock::operator()() {
    while(true) {
        this_thread::sleep_for(chrono::seconds(1));
        curr_time += chrono::duration<int>(1);
        {
            lock_guard<mutex> ln{mtx};
            cout << name << ": " << curr_time << "\n";
        }
    }


}