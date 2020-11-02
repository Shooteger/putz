#pragma once

#include <iostream>

class WorkPacket {
    private:
        int id;
    public:
        WorkPacket(int new_id) : id{new_id} {};
        void set_id(int new_id) {
            this->id = new_id;
        }
        const int get_id() {
            return this->id;
        }
};