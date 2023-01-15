/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BankAccount.h
 * Author: cse278
 * Copyright 2020 Karim Sammouri
 * Created on September 28, 2020, 4:21 PM
 */

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>

class BankAccount {
public:
    BankAccount(const std::string& owner = "", 
            const double balance = 0, 
            const std::string& address = "");
    BankAccount(const BankAccount& orig);
    virtual ~BankAccount();
    
    void depositMoney(double amount);
    void withdrawMoney(double amount);
    double getBalance();
    void updateAddress(const std::string& address);
    std::string& getAddress();
private:
    std::string owner;
    double balance;
    std::string address;
};

#endif /* BANKACCOUNT_H */

