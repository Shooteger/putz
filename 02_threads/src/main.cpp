#include <iostream>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

class Car {
    public:
    void operator()(string car_type) {
        int roundCar = 0;
        random_device r1;
        mt19937 gen{r1()};
        while(true) {
            uniform_real_distribution<> dis{1000, 10000};
            int sleep_time = dis(gen);
            this_thread::sleep_for(chrono::milliseconds(sleep_time));
            roundCar++;
            cout << "Car: " << car_type << "; Round: " << roundCar << "\n" << flush;
        }
    };
};

void letCarRace(string car_type) {
    int round = 0;
    random_device r2;
    mt19937 gen{r2()};
    while(true) {
        uniform_real_distribution<> dis{1000, 10000};
        int sleep_time2 = dis(gen);
        this_thread::sleep_for(chrono::milliseconds(sleep_time2));
        round++;
        cout << "Car: " << car_type << "; Round: " << round << "\n" << flush;
    }
}

int main() {
    Car car_object;

    thread car1 (letCarRace, "lada taiga");     
    thread car2 (car_object, "Opel Corsa");
    car1.join();
    car2.join();
}