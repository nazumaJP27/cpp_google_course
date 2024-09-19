#pragma once

#include "Card.h"
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
    void retain_card();   // Not implemented
    void eject_card();    // Not implemented
    int get_card_number();
};