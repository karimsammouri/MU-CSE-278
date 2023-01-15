/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SavingsAccount.h
 * Author: cse278
 * Copyright 2020 Karim Sammouri
 * Created on September 28, 2020, 10:26 PM
 */

#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H
#include <string>
#include "BankAccount.h"

class SavingsAccount : public BankAccount {
public:
    SavingsAccount(const std::string& owner = "", 
            const double balance = 0, 
            const std::string& address = "", 
            const double interest = 0);
    SavingsAccount(const SavingsAccount& orig);
    virtual ~SavingsAccount();
    
    double getInterestRate();
    void setInterestRate(double interest);
private:
    double interest;
};

#endif /* SAVINGSACCOUNT_H */

