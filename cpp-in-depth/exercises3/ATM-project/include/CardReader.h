#pragma once

#include "Card.h"
#include <iostream>

class ATM; // Forward declaration

class CardReader
{
    const ATM *const atm_;

public:
    // Constructor
    CardReader(const ATM *const atm);

    void read_card(const Card *card);
    void retain_card(const Card *card);
    void eject_card(const Card *card);
};