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
    Account accountT{1};
    thread t1{[&]() { cout << boolalpha << accountT.withdraw(1) << "\n" << flush; }};
    thread t2{[&]() { cout << boolalpha << accountT.withdraw(1) << "\n" << flush; }};
    t1.join();
    t2.join();
}
