#include "../include/CardReader.h"

// Constructor
CardReader::CardReader(const ATM *const atm) : atm_(atm), card_(nullptr) {}

bool CardReader::read_card(const Card *const card)
{
    if (card)
    {
        card_ = card;
        std::cout << "Card Inserted.\n";
        return true;
    }
    Message::display_content("Error reading the card...");
    return false;
}

void CardReader::eject_card()
{
    Message::display_content("Card " + card_->get_card_number() + " | " + card_->get_card_flag() + " ejected...");
    card_ = nullptr;
}

void CardReader::retain_card()
{
    Message::display_content("Card " + card_->get_card_number() + " | " + card_->get_card_flag() + " retained...");
}

std::string CardReader::get_card_number() const
{
    if (card_)
    {
        return card_->get_card_number();
    }
    else
    {
        Message::display_content("No card inserted");
    }
    return 0;
}