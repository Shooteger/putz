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
pid_t pid2;
int state;

void signal_handler(int signal) {
    cout << "pid1: " << pid1 << endl;
    cout << "pid2: " << pid2 << endl;
    waitpid(pid2, &state, 0);
    waitpid(pid2, &state, 0);
    quick_exit(EXIT_SUCCESS);
}

int main() {
    const char* env_aba_letter_a{getenv("ABA_LETTER_A")};
    const char* env_aba_letter_b{getenv("ABA_LETTER_B")};

    pid1 = fork();
    if (pid1 == 0) {    //child process
        if (env_aba_letter_a) {
            execl("/home/maurice/Documents/nvs5/exercises/putz/01_processes/build/charout", "charout", env_aba_letter_a);
        } else {
            execl("/home/maurice/Documents/nvs5/exercises/putz/01_processes/build/charout", "charout", "A");
        }
    } else {
        pid2 = fork();
        if (pid2 == 0) { 
            if (env_aba_letter_b) {
                execl("/home/maurice/Documents/nvs5/exercises/putz/01_processes/build/charout", "charout", env_aba_letter_b);
            } else {
                execl("/home/maurice/Documents/nvs5/exercises/putz/01_processes/build/charout", "charout", "B");
            }
        } else {
            this_thread::sleep_for(3s);
            cout << endl;
            kill(pid1, SIGKILL);
            kill(pid2, SIGKILL);
            signal(SIGCHLD, signal_handler);
        }
    }
}