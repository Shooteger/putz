#include <iostream>
#include <initializer_list>
#include <mutex>

#include "utils.h"

using namespace std;

recursive_mutex out_mtx;

void println() {
    lock_guard<recursive_mutex> lg{out_mtx};
    cout << "\n";
}

template<typename T, typename... Rest>
void println(const T& word, const Rest&... rest) {
    lock_guard<recursive_mutex> lg{out_mtx};
    cout << word << ' ';
    println(rest);
}