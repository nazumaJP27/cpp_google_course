#include "../include/Session.h"

Session::Session() : current_transaction_(TransactionType::NO_OP), active_account_(nullptr), transfer_target_(nullptr), transaction_amount_(nullptr) {}

bool Session::start_session(Account *active_account)
{
    active_account_ = active_account;
    // Check if the active_account Account pointer is not nullptr
    if (!active_account_)
    {
        std::cout << "Invalid active account...\n";
        return false;
    }
    return true;
}

void Session::reset_session()
{
    current_transaction_ = TransactionType::NO_OP;
    active_account_ = nullptr;
    transfer_target_ = nullptr;
    transaction_amount_ = nullptr;
}

bool Session::start_transaction(TransactionType transaction, Money *transaction_money, Account *transfer_target)
{
    // Check if the active_account Account pointer is not nullptr
    if (!active_account_)
    {
        std::cout << "Invalid active account for " << transaction_type_str(current_transaction_) << " operation...\n";
        return false;
    }

    current_transaction_ = transaction;
    // If the TransactionType == TRANSFER, check if the tranfer_targer is not nullptr and not equal to the active_account
    if (current_transaction_ == TransactionType::TRANSFER)
    {
        transfer_target_ = transfer_target;
        if (!transfer_target_ || transfer_target_ == active_account_)
        {
            std::cout << "Invalid target account for TRANSFER operation...\n";
            return false;
        }
    }

    transaction_amount_ = transaction_money;
    // Check if the transaction_money is not nullptr and not less than 1
    if (!transaction_amount_ || transaction_amount_->get_dollars() < 1)
    {
        std::cout << "Invalid money for " << transaction_type_str(current_transaction_) << " operation...\n";
        return false;
    }
    else
    {
        std::cout << "Active account:\n";
        active_account_->display();
        std::cout << "Transaction type: " << transaction_type_str(current_transaction_) << '\n';
        if (transfer_target_)
        {
            std::cout << "Target account:\n";
            transfer_target_->display();
        }
    }

    return true;
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
    active_account_->get_balance_()->add(transaction_amount_);
    reset_session();
}

void Session::withdraw_transaction()
{
    active_account_->get_balance_()->subtract(transaction_amount_);
    reset_session();
}

void Session::transfer_transaction()
{
    active_account_->get_balance_()->subtract(transaction_amount_);
    transfer_target_->get_balance_()->add(transaction_amount_);
    
    reset_session();
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