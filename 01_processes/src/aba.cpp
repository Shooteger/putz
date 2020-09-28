#include <iostream>
#include <thread>
#include <unistd.h>
#include <chrono>
#include <csignal>
#include <sys/wait.h>

using namespace std;

//declaration
pid_t pid1;
pid_t pid2;
int state;

int main() {
    chrono::milliseconds sleeptime(500);
    pid1 = fork();
    if (pid1 == 0) {    //child process
        while(true) {
            cout << "A" << endl;
            this_thread::sleep_for(sleeptime);
        }
    } else if (pid1 > 0) { //parent process
        while(true) {
            cout << "B" << endl;
            this_thread::sleep_for(sleeptime);
        }
    } else {
        cout << "fork failed" << endl;
    }
}