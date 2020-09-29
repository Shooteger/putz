#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void letCarRace(string car_type) {
    int round = 0;
    cout << "START!" << endl;
    while(true) {
        this_thread::sleep_for(chrono::seconds(1));
        round++;
        cout << "Car: " << car_type << "; Round: " << round << endl;
        cout << flush;
    }
}

int main() {
    thread car1 (letCarRace, "lada taiga"); 
    car1.join();
}
