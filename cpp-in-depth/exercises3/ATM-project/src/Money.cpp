#include "../include/Money.h"

// Constructors
Money::Money(int dollars) : cents_(dollars * 100) {}
Money::Money(int dollars, int cents) : cents_((dollars * 100) + cents) {}

// Methods
std::string Money::to_string() const
{
    std::ostringstream out;
    out << "$" << cents_ / 100 << '.' << std::setw(2) << std::setfill('0') << cents_ % 100;
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