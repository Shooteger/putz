#include <iostream>
#include <chrono>
#include <thread>

#include "CLI11.hpp"
#include "clock.h"
#include "pipe.h"

using namespace std;
using namespace CLI;

mutex out_mtx;

class Channel {
    public:
        Pipe<long>& get_pipe1() {return pipe1; }
        Pipe<long>& get_pipe2() {return pipe2; }
    private:
        Pipe<long> pipe1;
        Pipe<long> pipe2;
};

class TimeSlave {
    public:
        TimeSlave(string name_, Channel* cl=nullptr, int hours=0, int minutes=0, int seconds=0) : 
        name{name_}, curr_time{name_, hours, minutes, seconds}, channel{cl} {}

        void operator()() {
            long tmp;
            while (channel->get_pipe1() >> tmp) {
                unique_lock<mutex> ul{out_mtx};
                cout << name << ": " << curr_time.to_time() << endl;
                channel->get_pipe2() << curr_time.to_time();
            }
        }

        Channel* get_channel() {
            return channel;
        }
    private:
        string name;
        Clock curr_time;
        Channel* channel;
};

class TimeMaster {
    public:
        TimeMaster(string name_, Channel* cl1=nullptr, Channel* cl500 = nullptr, int hours=0, int minutes=0, int seconds=0) : 
        name{name_}, curr_time{name_, hours, minutes, seconds}, channel1{cl1}, channel2{cl500} {}

        void operator()() {
            channel1->get_pipe1() << 1u;
            channel2->get_pipe1() << 1u;
            channel1->get_pipe1() << 2u;
            channel2->get_pipe1() << 2u;
            channel1->get_pipe1() << 3u;
            channel2->get_pipe1() << 3u;

            this_thread::sleep_for(500ms);
            channel1->get_pipe1().close();
            channel2->get_pipe1().close();
        }

        void set_channel1(Channel* chan) {
            channel1 = chan;
        }

        void set_channel2(Channel* chan) {
            channel2 = chan;
        }

    private:
        string name;
        Clock curr_time;
        Channel* channel1;
        Channel* channel2;
};

int main() {
    
    //thread clock{Clock("testclock")};
    //clock.join();

    Channel c1;
    Channel cl500;


    thread tm{TimeMaster{"master", &c1, &cl500}};
    thread t1{TimeSlave{"slave1", &c1, 0, 10, 0}};
    thread t2{TimeSlave{"slave2", &cl500, 0, 20, 0}};

    tm.join();
    t1.join();
    t2.join();
}
