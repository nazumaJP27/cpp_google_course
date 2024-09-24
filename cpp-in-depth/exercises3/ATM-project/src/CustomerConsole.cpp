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
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Check the length of the card number and if it has only digits
        if (card_number_len < 15 || card_number_len > 16 || !std::all_of(card_number.begin(), card_number.end(), ::isdigit))
        {
            std::cout << "Invalid card number...\n";
            card_number.clear();
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

// Remove characters from reference string ('-', '.', ',', ' ')
void clean_str(std::string &dirt_str)
{
    //bool remove = [](char c) -> bool { return c == '-' || c == '.' || c == ',' || c == ' '; };

    std::string::iterator new_end = std::remove_if(dirt_str.begin(), dirt_str.end(), [](char c)
    { return c == '-' || c == '.' || c == ',' || c == ' '; });
    dirt_str.erase(new_end, dirt_str.end());
}
