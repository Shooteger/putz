#include <iostream>
#include <thread>

#include "account.h"

using namespace std;

Account::Account(int balance) {
    Account::balance = balance;
}

int Account::get_balance() {
    return Account::balance;
}

void Account::set_balance(int balance) {
    Account::balance = balance;
}

void Account::deposit(int amount) {
    Account::balance += amount;
}

bool Account::withdraw(int amount) {
    this_thread::yield();
    if ((Account::balance - amount) >= 0) {
        Account::balance -= amount;
        return true;
    } else
        return false;
}