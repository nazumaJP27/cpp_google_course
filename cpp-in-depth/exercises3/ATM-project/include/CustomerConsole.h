#pragma once

#include "Money.h"
#include "Session.h"
#include "Message.h"
#include <iostream>
#include <string>

class CustomerConsole
{
public:
    // Constructor
    CustomerConsole();

    // Methods
    std::string get_card_number();
    Money get_money();
    bool get_PIN(short const &account_PIN);
    TransactionType get_transaction();
    bool get_new_transaction();
};