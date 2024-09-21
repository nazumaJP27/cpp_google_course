#include "../include/Account.h"

Account::Account(std::string card_number, std::string card_flag, std::string name, double balance)
        : card_(Card(card_number, card_flag)), name_(name), balance_(Money((long) balance, (short) (balance * 100) % 100)) {}

void Account::display() const
{
    std::cout << "Name: " << get_name()
              << "\nCard: " << get_card_flag() << " - " << get_card_number()
              << "\nBalance: " << balance_.to_string() 
              << std::endl;
}