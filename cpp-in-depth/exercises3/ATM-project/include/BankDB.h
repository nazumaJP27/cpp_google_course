#pragma once

#include "Account.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class BankDB
{
    std::vector<Account> accounts_;
    bool bank_network_;

public:
    // Constructor
    BankDB(const std::string &bank_address);

    // Methods
    Account* get_account(const std::string &card_number);
    void update_account(const Account *account);
};