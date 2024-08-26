/* You have just gotten a position as a salesperson for the ExerShoe company,
specializing in high-end exercise shoes costing around $225 per pair.
Your boss has given you three options for compensation, which you must choose before you begin your first day:
1. Straight salary of $600 per week;
2. A salary of $7.00 per hour plus a 10% commission on sales;
3. No salary, but 20% commissions and $20 for each pair of shoes sold

Write a program to help decide the best choice of compensation (based on weekly sales). */

#include <ctype.h>  // isdigit
#include <iomanip>  // std::setprecision
#include <iostream>
#include <limits>   // std::numeric_limits
#include <string>   // std::stoi 

// Prototypes
float calc_option1(void);
float calc_option2(int WeeklySales);
float calc_option3(int WeeklySales);
int get_int(void);
bool str_isdigit(char *str);

// Compensation options variables
const float FIXED_SALARY = 600.00;  // For compensation option 1
const unsigned int WEEK_HOURS = 40; // For options 2 and 3 (week working time)
const float AVG_PAIR = 225.00;      // For options 2 and 3 (average cost of shoes)
const float PER_HOUR_SALARY = 7.00; // For compensation option 2
const float COMMISSION0 = 0.10;     // For compensation option 2
const float PER_PAIR = 20.00;       // For compensation option 3 (per pair compensation)
const float COMMISSION1 = 0.20;     // For compensation option 3

int main()
{
    // Set floating-point precision to display two decimal places and floatfield to fixed
    std::cout << std::fixed << std::setprecision(2);

    // Prompt for the number of weekly sales
    int weekly_sales = get_int();

    // Display the compensations for each option
    std::cout << "Option 1: $" << calc_option1()
              << "\nOption 2: $" << calc_option2(weekly_sales) 
              << "\nOption 3: $" << calc_option3(weekly_sales)
              << std::endl;
    return 0;
}

// Prompt for number of and returns it as an integer
int get_int(void)
{
    int input = 0;
    do
    {
        std::cout << "Weekly sales: ";
        if (!(std::cin >> input))
        {
            std::cin.clear();
            std::cout << "Invalid input. Only integers are allowed." << std::endl;
        }
        // Clear input buffer on every iteration
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (input <= 0);

    return input;
}

// Returns float salary for one week (fixed salary)
float calc_option1()
{
    return FIXED_SALARY;
}

// Returns float salary for one week (salary per hour with commissions)
float calc_option2(int WeeklySales)
{
    return (PER_HOUR_SALARY * WEEK_HOURS) + (WeeklySales * (AVG_PAIR * COMMISSION0));
}

// Returns float salary for one week (no salary but commissions, and a fixed per pair compensation)
float calc_option3(int WeeklySales)
{
    return (WeeklySales * (AVG_PAIR * COMMISSION1)) + (WeeklySales * PER_PAIR);
}