#pragma once

#include "Money.h"
#include <iostream>
#include <limits>

class ATM; // Forward declaration

class OperatorPanel
{
    ATM const *const atm_;

public:
    // Constructor
    OperatorPanel(const ATM *const atm);

    // Method
    Money get_initial_cash();
};