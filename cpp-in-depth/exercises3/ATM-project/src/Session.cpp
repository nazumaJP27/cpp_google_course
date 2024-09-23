#include "../include/Session.h"

Session::Session() : current_transaction_(TransactionType::NO_OP), active_account_(nullptr), transaction_amount_(0) {}

void Session::reset_session()
{
    current_transaction_ = TransactionType::NO_OP;
    active_account_ = nullptr;
    transaction_amount_ = Money(0);
}

void Session::start_transaction(TransactionType transaction, Account *account)
{
    current_transaction_ = transaction;
    active_account_ = account;
    if (active_account_)
    {
        std::cout << "Active account:\n";
        active_account_->display();
        std::cout << "Transaction type: " << transaction_type_str(transaction) << '\n';
    }
}

void Session::process_transaction()
{
    switch (current_transaction_)
    {
    case TransactionType::DEPOSIT:
        deposit_transaction();
        break;
    case TransactionType::WITHDRAW:
        withdraw_transaction();
        break;
    case TransactionType::TRANSFER:
        transfer_transaction();
        break;
    default:
        std::cout << "No active transaction...\n";
        break;
    }
}

void Session::deposit_transaction()
{

}

void Session::withdraw_transaction()
{

}

void Session::transfer_transaction()
{

}

void Session::display()
{
    std::cout << "Active account: ";
    if (active_account_)
    {
        active_account_->display();
        std::cout << "Operation: " << transaction_type_str(current_transaction_) << '\n';
    }
    else
    {
        std::cout << "-NO ACCOUNT-\n" << "Operation: -NO OPERATION-\n";
    }
}

std::string transaction_type_str(TransactionType type)
{
    if (type == TransactionType::DEPOSIT)
        return "DEPOSIT";
    else if (type == TransactionType::WITHDRAW)
        return "WITHDRAW";
    else if (type == TransactionType::TRANSFER)
        return "TRANSFER";
    else
        return "UNDEFINED";
}