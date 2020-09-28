#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <csignal>
#include <sys/wait.h>
#include <cstdlib>

using namespace std;

//declaration
pid_t pid1;
int childInt;


void kill_child_signal(int sigInt) {
    kill(getpid(), SIGKILL);
}

int main() {
    chrono::milliseconds sleeptime(500);
    pid1 = fork();
    if (pid1 == 0) {    //child process
        signal(SIGALRM, kill_child_signal);
        childInt = getpid();
        alarm(3);
        while(1) {
            cout << "A" << endl;
            this_thread::sleep_for(sleeptime);
        }
    } else if (pid1 > 0) { //parent process
        while(true) {
            cout << "B" << endl;
            this_thread::sleep_for(sleeptime);
        }
    }
}