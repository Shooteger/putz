#include <iostream>
#include <queue>

#include "work_packet.h"
#include "work_queue.h"

using namespace std;

void WorkQueue::push(WorkPacket packet) {
    unique_lock<mutex> ul{mtx};
    not_empty.wait(ul, [this](){ return (work_packets.size() < queue_size) ? 1 : 0; });
    work_packets.push(packet);
    not_empty.notify_one();
}

WorkPacket WorkQueue::pop() {
    unique_lock<mutex> ul{mtx};
    not_empty.wait(ul, [this](){ return work_packets.size(); });
    auto& wp = work_packets.front();
    work_packets.pop();
    not_empty.notify_one();
    return wp;
}