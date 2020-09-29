#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class Car {
    public:
    void operator()(string car_type) {
        int round = 0;
        cout << "START!" << endl;
        while(true) {
            this_thread::sleep_for(chrono::seconds(1));
            round++;
            cout << "Car: " << car_type << "; Round: " << round << "\n" << flush;
        }
    };
};

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
    //thread car1 (letCarRace, "lada taiga"); 
    //car1.join();
    Car car_object;
    thread car2 (car_object, "Opel Corsa");
    car2.join();
}