#pragma once

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>

#include "work_packet.h"

class WorkQueue {
    private:
        int queue_size;
        std::mutex mtx;
        std::condition_variable not_empty;
        std::queue<WorkPacket> work_packets;
    public:
        WorkQueue(int qs) : queue_size{qs} {
            if (queue_size <= 0) {
                throw std::logic_error("The size of the queue must be greater than 0!");
            }
        }
        void push(WorkPacket packet);
        WorkPacket pop();
}