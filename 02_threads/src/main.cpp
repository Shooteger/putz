#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <future>

using namespace std;

class Car {
    public:
    double total_time;

    void operator()(string car_type) {
        int roundCar = 0;
        random_device r1;
        mt19937 gen{r1()};
        double lap_time;
        while(roundCar < 10) {
            uniform_real_distribution<> dis{1000, 10000};
            int sleep_time = dis(gen);
            this_thread::sleep_for(chrono::milliseconds(sleep_time));
            roundCar++;
            lap_time = (sleep_time / double(1000));
            cout << "Car: " << car_type << "; Round: "  << roundCar << " Time: " << lap_time  << "s\n" << flush;
            set_total_time(lap_time);
        }
    }

    void set_total_time(double time) {
        total_time += time;
    }

    double get_total_time() { return total_time; }
};

double letCarRace(string car_type) {
    int round = 0;
    random_device r2;
    mt19937 gen{r2()};
    double lap_time;
    double total_lap_time;
    while(round < 10) {
        uniform_real_distribution<> dis{1000, 10000};
        int sleep_time2 = dis(gen);
        this_thread::sleep_for(chrono::milliseconds(sleep_time2));
        round++;
        lap_time = (sleep_time2 / double(1000));
        cout << "Car: " << car_type << "; Round: " << round << " Time: " << lap_time << "s\n" << flush;
        total_lap_time += lap_time;
    }
    return total_lap_time;
}

int main() {
    Car car_object;

    future<double> car1 = async(letCarRace, "Porsche Cayman S");

    //thread car1 (letCarRace, "Porsche Cayman S");     
    thread car2 (car_object, "Opel Corsa");
    //car1.join();
    car2.join();

    double car1Time = car1.get();
    double car2Time = car_object.get_total_time();

    if (car1Time > car2Time) {
        cout << "Winner: " << "Total Time: " << car2Time;
    } else {
        cout << "Winner: " << "Total Time: " << car1Time;
    }
}