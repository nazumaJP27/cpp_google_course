/* Exercise 1: Cricket chirps to temperature.
The common field cricket chirps in direct proportion to the current temperature.
Adding 40 to the number of time a cricket chirps in a minute, then dividing that value by 4 gives us the temperature.
TODO:
Write a program that takes as input the number of chirps in a minute and prints the current temperature. */

#include <iostream>
#include <limits>   //std::numeric_limits

// Prototypes
float chirps_to_temp(int n);

int main()
{
    int chirps = 0;

    // Prompt for number of chirps
    do
    {   std::cout << "Number of chirps (per minute):  " << std::flush;
        if (!(std::cin >> chirps))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Input error. Insert a integer number." << std::endl;
        }
    }
    while (chirps <= 0);

    // Print temperature based on the number of crirps per minute
    std::cout.precision(1);
    std::cout << std::fixed << "The approximate temperature is: " << chirps_to_temp(chirps) << " degrees Fahrenheit.\n";

    return 0;
}

float chirps_to_temp(int n)
{
    return (n + 40) / 4;
}