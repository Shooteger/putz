#include <iostream>
#include <initializer_list>

#include "philosopher.h"
#include "utils.h"

using namespace std;

void Philosopher::operator()() {
    while (true) {
        cout << "Philosopher " << id << " is thinking...\n";
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Philosopher " << id << " attempts to get left fork\n";
        left_fork->lock();
        this_thread::sleep_for(chrono::milliseconds(5000));
        
        cout << "Philosopher " << id << " got left fork. Now he wants the right one...\n";
        right_fork->lock();
        cout << "Philosopher " << id << " got right fork. Now he is eating...\n";
        this_thread::sleep_for(chrono::microseconds(2000));

        cout << "Philosopher " << id << " finished eating\n";
        left_fork->unlock();
        cout << "Philosopher " << id << " released left fork\n";
        right_fork->unlock();
        cout << "Philosopher " << id << " released right fork\n";
    }
}