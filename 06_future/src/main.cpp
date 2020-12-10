#include <iostream>
#include <vector>

#include "calc_factors.h"
#include "CLI11.hpp"


using namespace CLI;
using namespace std;

int main(int argc, char* argv[]) {
    vector<InfInt> numbers;

    vector<int> ref_nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

    App app{"Factor numbers"};
    app.add_option("number", numbers, "numbers to factor")->check(CLI::Number);

    CLI11_PARSE(app, argc, argv);
}
