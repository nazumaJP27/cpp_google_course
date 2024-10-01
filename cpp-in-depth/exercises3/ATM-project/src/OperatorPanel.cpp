#include "../include/OperatorPanel.h"

OperatorPanel::OperatorPanel(const ATM *const atm) : atm_(atm) {}

Money OperatorPanel::get_initial_cash()
{
    long double cash;
    do
    {
        std::cout << "Initial cash (only digits): $";
        if (!(std::cin >> cash))
        {
            std::cin.clear();
            std::cout << "Invalid input.\n";
        }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (cash < 1);

    // Return a Money object (constructor total cents)
    return Money(true, cash * 100);
}