/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SavingsAccount.cpp
 * Author: cse278
 * Copyright 2020 Karim Sammouri
 * Created on September 28, 2020, 10:26 PM
 */

#include "SavingsAccount.h"
#include <string>

SavingsAccount::SavingsAccount(const std::string& owner, 
        const double balance, 
        const std::string& address, 
        const double interest) :
BankAccount(owner, balance, address), 
        interest(interest) {
}

SavingsAccount::SavingsAccount(const SavingsAccount& orig) {
}

SavingsAccount::~SavingsAccount() {
}

double SavingsAccount::getInterestRate() {
    return interest;
}

void SavingsAccount::setInterestRate(double interest) {
    this->interest = interest;
}

