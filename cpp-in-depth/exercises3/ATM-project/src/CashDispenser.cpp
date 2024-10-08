#include "../include/CashDispenser.h"

// Constructor
CashDispenser::CashDispenser() : cash_on_hand_(Money(0)) {}

void CashDispenser::set_initial_cash(const Money *const initial_cash)
{
    cash_on_hand_.add(initial_cash);
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
        Message::display_content("Not enough cash on the ATM for this request...");
        return false;
    }
}