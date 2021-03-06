#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <future>
#include <iomanip>

using namespace std;

class Car {
    private:
        double total_time;
        string car_name;

    public:

        void operator()(string car_type, int laps) {
            set_car_name(car_type);
            car_name = car_type;
            int roundCar = 0;
            random_device r1;
            mt19937 gen{r1()};
            double lap_time;
            while(roundCar < laps) {
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
            this->total_time += time;
        }

        void set_car_name(string car_type) {
            this->car_name = car_type;
        }

        double get_total_time() { return this->total_time; }
        string get_car_name() {return this->car_name; }
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

void help() {
    cout << "Usage: contest [-h | --help | LAPS]\n";
    exit(0);
}

void error(string message="") {
    if (message != "") {
        cerr << message << "\n";
    }
    cerr << "Run with --help for more information.\n";
    exit(1);    
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        error("Minimum of one parameter required.");
    } else {
        size_t endpos;
        string first_arg = argv[1]; //at this point argv[1], tmp_laps could be -h or --help

        if (first_arg == "-h" || first_arg == "--help") {
            help();
        } else {
            try {
                int laps = stoi(argv[1], &endpos);
                if (1 <= laps and laps < 16) {
                    Car car_object;
                    Car car_object1;

                    thread car_1 (ref(car_object), "Opel Corsa", laps);
                    thread car_2 (ref(car_object1), "Porsche Cayman S", laps);

                    car_1.join();
                    car_2.join();

                    cout << fixed << setprecision(3);

                    double car1Time = car_object.get_total_time();
                    double car2Time = car_object1.get_total_time();

                    if (car1Time > car2Time) {
                        cout << "\nWinner: Porsche Cayman S\n" << "Total Time: " << car2Time << "s\n\n";
                        cout << "Loser: Opel Corsa S\n" << "Total Time: " << car1Time << "s\n";
                    } else if (car1Time < car2Time) {
                        cout << "\nWinner: Opel Corsa\n" << "Total Time: " << car1Time  << "s\n\n";
                        cout << "Loser: Porsche Cayman S\n" << "Total Time: " << car2Time << "s\n";
                    } else {
                        cout << "Draw!\n";
                    }
                } else {
                    error("Out of range (1 <= LAP'S < 16): " + first_arg);
                }
            } catch(const invalid_argument& ia) {
                error("Could not convert: " + first_arg + "\n" + ia.what());
            }
            
        }
    }

    /*
    future<double> car1 = async(letCarRace, "Porsche Cayman S");

    //thread car1 (letCarRace, "Porsche Cayman S");     
    thread car2 (ref(car_object), "Opel Corsa");
    //car1.join();
    car2.join();

    double car1Time = car1.get();
    double car2Time = car_object.get_total_time();

    if (car1Time > car2Time) {
        cout << "\nWinner: Porsche Cayman S\n" << "Total Time: " << car2Time << "\n";
        cout << "Loser: Opel Corsa S\n" << "Total Time: " << car1Time << "\n";
    } else {
        cout << "\nWinner: Opel Corsa\n" << "Total Time: " << car1Time  << "s" << "\n";
        cout << "Loser: Porsche Cayman S\n" << "Total Time: " << car2Time  << "s" << "\n";
    }
    */
}