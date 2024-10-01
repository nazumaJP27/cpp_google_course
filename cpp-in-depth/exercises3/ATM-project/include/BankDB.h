#pragma once

#include "Account.h"
#include "Message.h"
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
    void update_DB(const std::string &bank_address);
    void block_account(Account *const account) const { account->block(); }

    // Accessors
    bool get_bank_network() { return bank_network_; }
    unsigned int get_accounts_num() { return accounts_.size(); }
};