#pragma once

#include "Money.h"
#include <iostream>

class CashDispenser
{
    Money cash_on_hand_;

public:
    // Constructor
    CashDispenser();

    // Methods
    void set_initial_cash(const Money *const initial_cash);
    bool check_cash_on_hand(const Money *const amount);      // Check if there is enough cash on hand to satisfy a request
    bool dispense_cash(const Money *const amount);           // Dispense cash to the customer if cash_on_hand_ <= amount
    void print_cash_on_hand();
};