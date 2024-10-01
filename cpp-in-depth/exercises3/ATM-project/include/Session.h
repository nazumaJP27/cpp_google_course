#pragma once

#include "Account.h"
#include "Money.h"
#include "Message.h"
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
    Account *transfer_target_;
    Money *transaction_amount_;

public:
    // Constructor
    Session();

    // Methods
    bool start_session(Account *active_account);
    void reset_session();
    bool start_transaction(TransactionType transaction, Money *transaction_money, Account *transfer_target=nullptr);
    void process_transaction();
    void display();

    // Accessors
    const Account* get_active_account() const { return active_account_; }

private:
    void deposit_transaction();
    void withdraw_transaction();
    void transfer_transaction();
};