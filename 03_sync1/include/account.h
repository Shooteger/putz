#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <functional>
#include <thread>

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

class Depositer {
    private:
        Account& account;
    public:
        Depositer(Account& account_ref)  : account(account_ref);

        void operator()() {
            for (int i{0}; i < 5; ++i) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100) * i);
                account.deposit(1);
            }
        }
}

#endif