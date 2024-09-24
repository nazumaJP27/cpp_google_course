#include "../include/Account.h"

Account::Account(std::string card_number, std::string card_flag, short PIN, std::string name, Money balance)
        : card_(Card(card_number, card_flag)), PIN_(PIN), name_(name), balance_(balance) {}

void Account::display() const
{
    std::cout << "Name: " << get_name()
              << "\nCard: " << get_card_flag() << " | " << get_card_number()
              << "\nPIN: " << get_PIN()
              << "\nBalance: " << balance_.to_string() 
              << std::endl;
}