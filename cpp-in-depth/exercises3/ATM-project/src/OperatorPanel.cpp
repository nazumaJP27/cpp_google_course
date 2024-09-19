#include "../include/OperatorPanel.h"

OperatorPanel::OperatorPanel(const ATM *const atm) : atm_(atm) {}

Money OperatorPanel::get_initial_cash()
{
    double cash;
    do
    {
        std::cout << "Amount of money currently in the cash dispenser: $";
        if (!(std::cin >> cash))
        {
            std::cin.clear();
            std::cout << "Invalid input.\n";
        }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (cash < 1);

    // Return a Money object (constructor @param[0] dollars, @param[1] cents)
    return Money((int) cash, (int) (cash * 100) % 100);
}