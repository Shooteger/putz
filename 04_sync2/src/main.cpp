#include <iostream>
#include <thread>
#include <functional>
#include <random>
#include <iomanip>

#include "work_queue.h"
#include "work_packet.h"

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
        cout << "W" << id << ": Processed work packet" << wp.get_id() << "\n";
        cout << fixed << setprecision(2);
    }
}

int main() {
    WorkQueue wq{10};

    int cnt{0};

    thread t1{worker, 1, ref(wq)};
    thread t2{worker, 2, ref(wq)};
    thread t3{worker, 3, ref(wq)};

    while (true) {
        //time_out = dis(gen);
        this_thread::sleep_for(chrono::milliseconds((int) 500));
        wq.push(WorkPacket{cnt});
        cout << "B: Submitted work packet " << cnt << "\n";
        cout << fixed << setprecision(2);
        cnt++;
    }

    t1.join();
    t2.join();
    t2.join();

}
