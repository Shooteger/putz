#include <iostream>
#include <thread>

#include "account.h"

using namespace std;

int main() {
    
    //Punkt 1
    /*
    Account account{15};
    cout << "Bestand: " << account.get_balance() << "€\n" << flush;
    account.withdraw(6);
    cout << "Bestand: " << account.get_balance() << "€\n" << flush;
    */

    //Punkt 2
    /*
    Account accountT{1};
    thread t1{[&]() { cout << boolalpha << accountT.withdraw(1) << "\n" << flush; }};
    thread t2{[&]() { cout << boolalpha << accountT.withdraw(1) << "\n" << flush; }};
    t1.join();
    t2.join();
    */

    //Punkt 3-7
    Account accountT1{0};
    Depositer d1{accountT1};
    Depositer d2{accountT1};

    thread t11{ref(d1)};
    thread t22{ref(d2)};

    t11.join();
    t22.join();

    cout << accountT1.get_balance() << "\n" << flush;
}
