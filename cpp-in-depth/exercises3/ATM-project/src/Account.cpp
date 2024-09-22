#include "../include/Account.h"

Account::Account(std::string card_number, std::string card_flag, std::string name, int dollars, short cents)
        : card_(Card(card_number, card_flag)), name_(name), balance_(Money(dollars, cents)) {}

void Account::display() const
{
    std::cout << "Name: " << get_name()
              << "\nCard: " << get_card_flag() << " | " << get_card_number()
              << "\nBalance: " << balance_.to_string() 
              << std::endl;
}