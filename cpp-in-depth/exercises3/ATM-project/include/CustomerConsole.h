#pragma once

#include "Money.h"
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
};