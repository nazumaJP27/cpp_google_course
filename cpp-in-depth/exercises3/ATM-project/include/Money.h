#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

class Money
{
    unsigned long long cents_;

public:
    // Constructors
    Money(int dollars);
    Money(int dollars, int cents);
    Money(bool cents_value=false, unsigned long long cents=0);

    // Methods
    std::string to_string(bool cents=false) const;
    void add(const Money *const amount);
    void subtract(const Money *const amount);
    bool greater_equal(const Money *const compare_to) const;
    double get_money() const { return cents_ * 100; }
};