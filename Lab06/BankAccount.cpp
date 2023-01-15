/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BankAccount.cpp
 * Author: cse278
 * Copyright 2020 Karim Sammouri
 * Created on September 28, 2020, 4:21 PM
 */

#include "BankAccount.h"
#include <string>

BankAccount::BankAccount(const std::string& owner, 
        const double balance, 
        const std::string& address) {
    this->owner = owner;
    this->balance = balance;
    this->address = address;
}

BankAccount::BankAccount(const BankAccount& orig) {
}

BankAccount::~BankAccount() {
}

void BankAccount::depositMoney(double amount) {
    if (amount > 0) {
    balance += amount;
    }
}

void BankAccount::withdrawMoney(double amount) {
    if (amount > 0 && balance >= amount) {
    balance -= amount;
    }
}

double BankAccount::getBalance() {
    return balance;
}

void BankAccount::updateAddress(const std::string& address) {
    this->address = address;
}

std::string& BankAccount::getAddress() {
    return address;
}

