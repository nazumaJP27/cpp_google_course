#pragma once

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
    double get_initial_cash();
};