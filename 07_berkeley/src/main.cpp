#include <iostream>
#include <chrono>
#include <thread>

#include "CLI11.hpp"
#include "clock.h"
#include "pipe.h"

using namespace std;
using namespace CLI;

class Chnanel {
    public:
        Pipe<long>& get_pipe1() {return pipe1; }
        Pipe<long>& get_pipe2() {return pipe2; }
    private:
        Pipe<long> pipe1;
        Pipe<long> pipe2;
};

class TimeSlave {
    public:
        TimeSlave(string name_, int hours=0, int minutes=0, int seconds=0) : name{name_}, curr_time{name_, hours, minutes, seconds} {}
    private:
        string name;
        Clock curr_time;
};

class TimeMaster {
    public:
        TimeMaster(string name_, int hours=0, int minutes=0, int seconds=0) : name{name_}, curr_time{name_, hours, minutes, seconds} {}
    private:
        string name;
        Clock curr_time;
};

int main() {
    
    //thread clock{Clock("testclock")};
    //clock.join();

    thread t1{TimeSlave{"slave1", 0, 10, 0}};
    thread t2{TimeSlave{"slave2", 0, 20, 0}};

    t1.join();
    t2.join();
}
