#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <csignal>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) {
    chrono::milliseconds sleeptime(500);
    while (true) {
        cout << argv[1] << flush;
        this_thread::sleep_for(sleeptime);
    }
}