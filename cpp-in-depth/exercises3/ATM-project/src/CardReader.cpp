#include "../include/CardReader.h"

// Constructor
CardReader::CardReader(const ATM *const atm) : atm_(atm), card_(nullptr) {}

bool CardReader::read_card(const Card *const card)
{
    if (card)
    {
        card_ = card;
        std::cout << "Card Inserted\n";
        return true;
    }
    std::cout << "Invalid Card\n";
    return false;
}

int CardReader::get_card_number()
{
    if (card_)
    {
        return card_->get_card_number();
    }
    return 0;
}