#include <iostream>
#include <thread>
#include <functional>

#include "work_queue.h"
#include "work_packet.h"

using namespace std;

int main() {
    WorkQueue wq{10};

    int cnt{0};

    while (true) {
        //time_out = dis(gen);
        this_thread::sleep_for(chrono::milliseconds((int) 500));
        wq.push(WorkPacket{cnt});
        cout << "B: Submitted work packet " << cnt << "\n";
        cnt++;
    }

}
