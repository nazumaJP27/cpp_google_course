#pragma once

#include "Account.h"
#include "Money.h"
#include <iostream>

enum TransactionType
{
    NO_OP = 0, DEPOSIT, WITHDRAW, TRANSFER,
};

// Return a string with the type
std::string transaction_type_str(TransactionType type);

class Session
{
    TransactionType current_transaction_;
    Account *active_account_;
    Money transaction_amount_;

public:
    // Constructor
    Session();

    // Methods
    void start_transaction(TransactionType transaction, Account *account);
    void process_transaction();
    void reset_session();
    void display();

private:
    void deposit_transaction();
    void withdraw_transaction();
    void transfer_transaction();
};