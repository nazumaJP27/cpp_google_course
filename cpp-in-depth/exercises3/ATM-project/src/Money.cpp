#include "../include/Money.h"

// Constructors
Money::Money(int dollars) : cents_(dollars * 100) {}
Money::Money(int dollars, int cents) : cents_((dollars * 100) + cents) {}
Money::Money(bool cents_value, unsigned long long cents) : cents_(cents) {}

// Methods
std::string Money::to_string(bool cents) const
{
    // Lambda to format large numbers with commas
    auto add_commas = [](unsigned long long n) -> std::string {
        std::string formated_n = std::to_string(n);
        short insert_pos = formated_n.length() - 3;
        for (; insert_pos > 0; insert_pos -= 3)
            formated_n.insert(insert_pos, ",");
        return formated_n;
    };

    std::ostringstream out;
    if (!cents)
    {
        out << '$' << add_commas(cents_ / 100) << '.' << std::setw(2) << std::setfill('0') << cents_ % 100;
    }
    else
        out << cents_;

    return out.str();
}

void Money::add(const Money *const amount)
{
    // Check for nullptr
    if (amount)
        cents_ += amount->cents_;
}

void Money::subtract(const Money *const amount)
{
    // Check for nullptr
    if (amount)
    {    if (greater_equal(amount))
            cents_ -= amount->cents_;
    }
    else
        std::cout << "Not enough money to subtract.\n";
}

bool Money::greater_equal(const Money *const compare_to) const
{
    return cents_ >= compare_to->cents_;
}