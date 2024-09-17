#pragma once

class Card
{
    int number_;

public:
    // Constructor
    Card(int number) : number_(number) {}

    int get_card_number() const { return number_; }
};