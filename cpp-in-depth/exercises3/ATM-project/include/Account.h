#pragma once

#include "Card.h"
#include "Money.h"
#include <iostream>
#include <string>

class Account
{
    const Card card_;
    short PIN_;
    const std::string name_;
    Money balance_;

public:
    // Constructor
    Account(std::string card_number, std::string card_flag, short PIN, std::string name, Money balance);

    // Accessors
    std::string get_card_number() const { return card_.get_card_number(); }
    std::string get_card_flag() const { return card_.get_card_flag(); }
    int get_PIN() const { return PIN_; }
    std::string get_name() const { return name_; }
    const Money* get_balance() const { return &balance_; }
    Money* get_balance_() { return &balance_; } // For operations (will be private)

    // Methods
    void display() const;
};