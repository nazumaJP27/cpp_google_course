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
    long double get_dollars() const { return cents_ / 100; }

    // Mutators
    void spend_all() { cents_ = 0; }
    void set_dollars(long long dollars, short cents=0) { cents_ = (dollars * 100) + cents; }
    void set_money(const Money money) { cents_ = money.cents_; }
};