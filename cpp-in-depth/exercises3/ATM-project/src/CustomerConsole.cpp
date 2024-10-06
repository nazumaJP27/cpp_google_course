#include "../include/CustomerConsole.h"

#include <algorithm> // std::remove_if, std::all_of
#include <cctype>    // std::isdigit
#include <limits>    // std::numeric_limits

void clean_str(std::string &dirt_str);

CustomerConsole::CustomerConsole() {}

std::string CustomerConsole::get_card_number()
{
    std::string card_number;
    short card_number_len;
    do
    {
        std::cout << "Input a card number (15-16 digits): ";
        std::getline(std::cin, card_number);

        clean_str(card_number);
        card_number_len = card_number.length();

        // Check the length of the card number and if it has only digits
        if (card_number_len < 15 || card_number_len > 16 || !std::all_of(card_number.begin(), card_number.end(), ::isdigit))
        {
            std::cout << "Invalid card number...\n";
            card_number.clear();
        }
    } while (card_number.empty());

    return card_number;
}

Money CustomerConsole::get_money()
{
    long double in_money;
    do
    {
        std::cout << "Money amount (only digits): $";
        if (!(std::cin >> in_money))
        {
            std::cin.clear();
            std::cout << "Invalid input.\n";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (in_money < 1);

    return Money(true, in_money * 100);
}

bool CustomerConsole::get_PIN(short const &account_PIN)
{
    for (short attempts = 3, in_PIN; attempts > 0; --attempts)
    {
        std::cout << "Insert PIN (4 digits): ";
        if (!(std::cin >> in_PIN) || in_PIN != account_PIN)
        {
            std::cin.clear();
            std::cout << "Invalid input.\n";
        }
        else if (in_PIN == account_PIN)
            return true;

        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cout << "Too many invalid inputs...\n";
    return false;
}

TransactionType CustomerConsole::get_transaction()
{
    short input;
    
    do
    {
        std::cout << "1) DEPOSIT\n2) WITHDRAW\n3) TRANSFER\n0) CANCEL\n";
        if (!(std::cin >> input) || input < 0 || input > 3)
        {
            std::cin.clear();
            std::cout << "Invalid input. Please enter a number between 0 and 3.\n";
            input = -1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (input < 0);

    // Cast the integer input to the TransactionType enum
    return static_cast<TransactionType>(input);
}

bool CustomerConsole::get_new_transaction()
{
    short input = -1;

    std::cout << "Do you wish to make another transaction?\n";
    for (short attempts = 3; attempts > 0 && input < 0; --attempts)
    {
        std::cout << "1) YES\n0) NO\n";
        if (!(std::cin >> input) || input < 0 || input > 1)
        {
            std::cin.clear();
            std::cout << "Invalid input.\n";
            input = -1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (input == 1)
        return true;
    return false;
}

// Remove characters from reference string ('-', '.', ',', ' ')
void clean_str(std::string &dirt_str)
{
    std::string::iterator new_end = std::remove_if(dirt_str.begin(), dirt_str.end(), [](char c)
    { return c == '-' || c == '.' || c == ',' || c == ' '; });

    dirt_str.erase(new_end, dirt_str.end());
}
