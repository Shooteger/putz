#include "semaphore.h"

using namespace std;


void Semaphore::aquire() {
    unique_lock<mutex> ul{mtx};
    while (cnt == 0) {
        not_empty.wait(ul);
    }
    cnt--;
}

void Semaphore::release() {
    unique_lock<mutex> ul{mtx};
    cnt++;
    not_empty.notify_one();
}

int Semaphore::available_permits() {
    return cnt;
}