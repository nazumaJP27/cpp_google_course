#include "../include/BankDB.h"

BankDB::BankDB(const std::string &bank_address)
{
    // Construct an ifstream object and display its contents
    std::ifstream file(bank_address);

    // Checks if could open file
    if (!file)
    {
        bank_network_ = false;
        std::cout << "Could not open file: " << bank_address << std::endl;
    }
    else
    {
        bank_network_ = true;
        std::cout << "File " << bank_address << " openned...\n";
        
        std::string line, card_number, card_flag, name, balance_str;
        double balance;
        while (std::getline(file, line))
        {
            std::istringstream line_stream(line);

            // Parse the istringstream object (format: cardnumber, card flag, name, balance)
            std::getline(line_stream, card_number, ',');
            std::getline(line_stream, card_flag, ',');
            std::getline(line_stream, name, ',');
            std::getline(line_stream, balance_str, ',');

            // Convert balance to double
            balance = std::stod(balance_str);

            // Create an Account object and add it to the vector
            accounts_.emplace_back(card_number, card_flag, name, balance);
        }
    }
    file.close();
}

Account* BankDB::get_account(const std::string &card_number)
{
    for (int i = 0; i < accounts_.size(); ++i)
    {
        if (accounts_[i].get_card_number() == card_number)
            return &accounts_[i];
    }

    std::cout << "No matching account for card number " << card_number << " found...\n";
    return nullptr;
}

void BankDB::update_account(const Account *account)
{
    // Will update the balance of an account in the CSV file after a operation on the given Account object
}