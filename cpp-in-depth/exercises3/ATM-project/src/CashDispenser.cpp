#include "../include/CashDispenser.h"

// Constructor
CashDispenser::CashDispenser() : cash_on_hand_(Money(0)) {}

void CashDispenser::set_initial_cash(const Money *const initial_cash)
{
    cash_on_hand_.add(initial_cash);
    std::cout << "Initial cash: ";
    print_cash_on_hand();
    std::cout << '\n';
}

bool CashDispenser::check_cash_on_hand(const Money *const amount) const
{
    if (cash_on_hand_.greater_equal(amount))
        return true;
    return false;
}

bool CashDispenser::dispense_cash(const Money *const amount)
{
    if (check_cash_on_hand(amount))
    {
        cash_on_hand_.subtract(amount);
        return true;
    }
    else
    {
        std::cout << "Not enough cash on the ATM for the request...\n";
        return false;
    }
}
void CashDispenser::print_cash_on_hand()
{
    std::cout << cash_on_hand_.to_string();
}