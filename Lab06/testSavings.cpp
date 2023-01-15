// Copyright 2020 Christopher Vendome
#include <iostream>
#include <fstream>
#include <string>
#include "SavingsAccount.h"

int main() {
    SavingsAccount testAccount1("John Doe", 18000.00, "Main Street", 3);
    testAccount1.depositMoney(200);
    testAccount1.withdrawMoney(11000);
    testAccount1.setInterestRate(5.3);

    std::cout << "Test 1: " << testAccount1.getBalance() << " "
           << testAccount1.getAddress() << " " 
           << testAccount1.getInterestRate() << std::endl;

    SavingsAccount testAccount2("Jane Doe", 5000.00, "Miami Place", 2.1);
    testAccount2.depositMoney(1000.00);
    testAccount2.withdrawMoney(5000.00);
    testAccount2.setInterestRate(7.32);

    std::cout << "Test 2: " << testAccount2.getBalance() << " "
           << testAccount2.getAddress() << " " 
           << testAccount2.getInterestRate() << std::endl;

    SavingsAccount testAccount3("Bob", 1000.98, "Orange Grove", 8.25);
    testAccount3.depositMoney(22.38);
    testAccount3.withdrawMoney(36.71);
    testAccount3.setInterestRate(2);

    std::cout << "Test 3: " << testAccount3.getBalance() << " "
           << testAccount3.getAddress() << " " 
           << testAccount3.getInterestRate() << std::endl;

    return 0;
}
