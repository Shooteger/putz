/*
 * Documentation:
 * https://en.cppreference.com/w/cpp/thread/shared_future
 * http://www.cplusplus.com/reference/string/string/find_first_not_of/
*/

#include <iostream>
#include <vector>
#include <future>
#include <thread>

#include "calc_factors.h"
#include "CLI11.hpp"


using namespace CLI;
using namespace std;

void calc_res(vector<InfInt>& number_vec, shared_future<vector<InfInt>>& async_num_vec) {
    //measuring time part 1
    auto start = chrono::system_clock::now();

    for (auto num : number_vec) {
        cout << num << ": ";
        async_num_vec = async(get_factors, num);

        for (auto prim : async_num_vec.get()) {
            cout << prim << " ";
        }
        cout << "\n";
    }

    //measuring time part 2
    auto duration = chrono::duration_cast<chrono::milliseconds>(std::chrono::system_clock::now() - start);
    cout << "Time elapsed used for factoring: " << duration.count() << "ms\n";
}

int main(int argc, char* argv[]) {
    vector<InfInt> numbers;
    shared_future<vector<InfInt>> async_num_vec;

    //cmd.find_first_not_of(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);

    App app{"Factor numbers"};
    app.add_option("number", numbers, "numbers to factor")->check(CLI::Number);
    app.add_flag("-a,--async", "async");

    CLI11_PARSE(app, argc, argv);
    
    thread res_thread{calc_res, ref(numbers), ref(async_num_vec)};

    res_thread.join();    
}
