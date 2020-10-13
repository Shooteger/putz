#include <iostream>

#include "account.h"

using namespace std;

int main() {
    Account account{15};
    cout << "Bestand: " << account.get_balance() << "€\n" << flush;
    account.withdraw(6);
    cout << "Bestand: " << account.get_balance() << "€\n" << flush;
}
