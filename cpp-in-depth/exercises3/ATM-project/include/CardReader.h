#pragma once

#include "Card.h"
#include "Message.h"
#include <iostream>

class ATM; // Forward declaration

class CardReader
{
    const ATM *const atm_;
    const Card *card_;

public:
    // Constructor
    CardReader(const ATM *const atm);

    // Methods
    bool read_card(const Card *const card);
    void retain_card();
    void eject_card();
    std::string get_card_number() const;
};