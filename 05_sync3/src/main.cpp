#include <iostream>
#include <mutex>
#include <thread>

#include "philosopher.h"
#include "CLI11.hpp"

using namespace std;

int main(int argc, char** argv) {

    CLI::App app("Dining philosophers simulation");
    long unsigned int size;
    int nodeadlock;
    int livelock;

    app.add_option("nodeadlock", nodeadlock, "Prevent a deadlock at all" )->required();
    app.add_option("livelock", livelock, "Prevent a deadlock at all" )->required();
    
    CLI11_PARSE(app, argc, argv);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    mutex m1;
    mutex m2;
    mutex m3;
    mutex m4;
    mutex m5;

    Philosopher p1{1, &m1, &m2};
    Philosopher p2{2, &m2, &m3};
    Philosopher p3{3, &m3, &m4};
    Philosopher p4{4, &m4, &m5};
    Philosopher p5{5, &m5, &m1};  

    thread t1{[&](){ p1(); }};
    thread t2{[&](){ p2(); }};
    thread t3{[&](){ p3(); }};
    thread t4{[&](){ p4(); }};
    thread t5{[&](){ p5(); }};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}
