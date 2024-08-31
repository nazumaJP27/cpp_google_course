/* Exercise 3: Time in seconds to hours, minutes, and seconds.
Example run:
---------------------------------------------
Number of seconds: 3662
Hours: 1
Minutes: 1
Seconds: 2 
---------------------------------------------
TODO:
Write a program that takes as input a time period given in seconds,
and outputs the number of hours, minutes and seconds it represents. */

#include <iostream>
#include <limits>   // std::numeric_limits
#include <string>

// Constants
constexpr unsigned int SECS_MINUTE = 60;
constexpr unsigned int SECS_HOUR = 60 * SECS_MINUTE;

// Prototypes
int get_seconds(const std::string &prompt="");

int main()
{
    // Prompt for time in seconds
    int total_secs = get_seconds("Number of seconds: ");

    // Convert total seconds into hours, minutes and seconds
    int hours = total_secs / SECS_HOUR;
    int minutes = (total_secs % SECS_HOUR) / SECS_MINUTE;
    int seconds = total_secs % 60;

    // Print the result of each conversion
    std::cout << "Hours: " << hours << "\nMinutes: " << minutes << "\nSeconds: " << seconds << std::endl;
    return 0;
}

// Prompt [custom prompt], validate and return int input
int get_seconds(const std::string &prompt)
{
    int input = 0;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> input))
        {
            std::cin.clear();
            std::cout << "Invalid input." << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (input <= 0);

    return input;
}