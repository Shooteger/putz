#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <functional>

class Account {
    private:
        int balance{0};
    public:
        int get_balance();
        Account(int balance);
        void set_balance(int amount);
        void deposit(int amount);
        bool withdraw(int amount);
};

#endif