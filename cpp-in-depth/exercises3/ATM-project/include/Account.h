#pragma once

#include "Card.h"
#include "Money.h"
#include <iostream>
#include <string>

class Account
{
    friend class BankDB;

    const Card card_;
    bool valid_;             // 0 == BLOCKED, 1 == VALID
    short PIN_;
    const std::string name_;
    Money balance_;

public:
    // Constructor
    Account(std::string card_number, std::string card_flag, bool valid, short PIN, std::string name, Money balance);

    // Accessors
    std::string get_card_number() const { return card_.get_card_number(); }
    std::string get_card_flag() const { return card_.get_card_flag(); }
    short get_valid() const { return valid_ ? 1 : 0; }
    short get_PIN() const { return PIN_; }
    std::string get_name() const { return name_; }
    const Money* get_balance() const { return &balance_; }
    Money* get_balance_() { return &balance_; } // For operations (will be private)

    // Methods
    void display() const;

private:
    void block() { valid_ = false; }
};