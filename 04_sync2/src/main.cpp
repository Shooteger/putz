#include <iostream>
#include <thread>
#include <functional>
#include <random>
#include <iomanip>

#include "work_queue.h"
#include "work_packet.h"
#include "CLI11.hpp"

using namespace std;

void worker(int id, WorkQueue& wq) {
    random_device rd;
    mt19937 gen{rd()};
    uniform_int_distribution<> dis(1000, 10000);
    float timeout;

    while (true) {
        timeout = dis(gen);
        cout << "W" << id << ": Want work packets\n";
        auto wp = wq.pop();
        cout << "W" << id << ": Got work packet " << wp.get_id() << "\n";
        this_thread::sleep_for(chrono::milliseconds((int) timeout));
        cout << "W" << id << ": Processed work packet" << wp.get_id() << " (";
        cout << fixed << setprecision(2);
        cout << timeout / 1000 << "s)\n";
    }
}

int main(int argc, char** argv) {

    CLI::App app("Boss and worker simulation");
    long unsigned int size;

    app.add_option("size", size, "Size of the queue" )->required();
    
    CLI11_PARSE(app, argc, argv);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        return app.exit(e);
    }

    WorkQueue wq{size};

    int cnt{0};

    random_device rd;
    mt19937 gen{rd()};
    uniform_int_distribution<> dis{0, 1000};
    float timeout;

    thread t1{worker, 1, ref(wq)};
    thread t2{worker, 2, ref(wq)};
    thread t3{worker, 3, ref(wq)};

    while (true) {
        timeout = dis(gen);
        this_thread::sleep_for(chrono::milliseconds((int) 500));
        wq.push(WorkPacket{cnt});
        cout << "B: Submitted work packet " << cnt << " (";
        cout << fixed << setprecision(2);
        cout << timeout / 1000 << "s)\n";
        cnt++;
    }

    t1.join();
    t2.join();
    t2.join();
}
