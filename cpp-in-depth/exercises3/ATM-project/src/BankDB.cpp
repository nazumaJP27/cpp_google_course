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
        unsigned long long balance;
        while (std::getline(file, line))
        {
            balance = 0;
            if (!(std::isspace(line[0])))
            {
                std::istringstream line_stream(line);

                // Parse the istringstream object (format: cardnumber, card flag, name, balance [in cents])
                std::getline(line_stream, card_number, ',');
                std::getline(line_stream, card_flag, ',');
                std::getline(line_stream, name, ',');
                std::getline(line_stream, balance_str, ',');

                // Convert balance to unsigned long long (total cents)
                balance = std::stoull(balance_str);

                // Create an Account object and add it to the vector
                accounts_.emplace_back(card_number, card_flag, name, Money(true, balance));
            }
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

// Will update the balance of the accounts in the CSV file
void BankDB::update_DB(const std::string &bank_address)
{
    std::ofstream file(bank_address);
    for (const Account &account : accounts_)
    {
        file << account.get_card_number() << ','
             << account.get_card_flag() << ','
             << account.get_name() << ','
             << account.get_balance()->to_string(true) << '\n'; // sign=false
    }
    std::cout << "Bank Database updated...\n";
    file.close();
}