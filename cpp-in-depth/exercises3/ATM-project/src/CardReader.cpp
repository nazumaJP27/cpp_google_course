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

void CardReader::eject_card()
{
    std::cout << "Card " << card_->get_card_number() << " ejected...\n";
    card_ = nullptr;
}

std::string CardReader::get_card_number() const
{
    if (card_)
    {
        return card_->get_card_number();
    }
    else
    {
        std::cout << "No card inserted\n";
    }
    return 0;
}