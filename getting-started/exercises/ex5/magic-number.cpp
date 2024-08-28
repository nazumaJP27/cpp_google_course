/* Exercise 5: "Magic number" problem.

Example run:
---------------------------------------------
input number: 901
reverse it: 109
subtract: 901 - 109 = 792
reverse it: 297
add: 297 + 792 = 1089   
---------------------------------------------
TODO:
Write a program that prompts the user to enter a three-digit number whose first digit is greater than its last.
Your program will reverse the number, and subtract the reversal from the original number.
Finally, reverse the resulting number, and add it to its unreversed form.
Output the final result.
OBS: The original number that the user enters must be of integer type (not three chars). */

#include <iostream>
#include <limits>
#include <string>

// Prototypes
int get_three_digit_number(const std::string &prompt="Number: ");
int flip_int(int x);


int main()
{
    std::cout << "\nEnter a three-digit number whose first digit is greater than the third." << std::endl;
    int number = 0;

    // Prompt for number in a loop while the first digit < last digit
    do
    {
        number = get_three_digit_number();
    }
    while ((number / 100) <= (number % 10));
    std::cout << "-------------------------\n";

    // Display the input number and the subsequent steps
    std::cout << "input number: " << number << std::endl;

    // Create a var for the reversed number
    int reversed = flip_int(number);
    std::cout << "reverse it: " << reversed << std::endl;

    // Subtract the reversed number from the input number
    std::cout << "subtract: " << number << " - " << reversed << " = ";
    number -= reversed;
    std::cout << number << std::endl;

    // Reverse number again and print reversed + number to the console
    reversed = flip_int(number);
    std::cout << "reverse it: " << reversed << std::endl;

    // Sum reversed + number
    std::cout << "add: " << reversed << " + " << number << " = ";
    number += reversed;
    std::cout << number << std::endl;

    return 0;
}

// Prompt [custom prompt] in a loop, validate (3-digit && first > third) and return input
int get_three_digit_number(const std::string &prompt)
{
    int input = 0;
    do
    {
        std::cout << prompt;
        // Prompt and check for flag errors
        if (!(std::cin >> input))
        {
            std::cin.clear();
            std::cout << "Invalid input." << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (input < 100 || input > 999);
    return input;
}

// Reverse and return an integer number (value)
int flip_int(int x)
{
    int fliped = 0;
    while (x)
    {
        fliped = fliped * 10 + (x % 10);
        x /= 10;
    }
    return fliped;
}