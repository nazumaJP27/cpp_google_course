/* Our task is to write a program that implements a guessing game.
Our program generates a random number between 0 and 100. The player
must guess the secret number. The program provides hints like "that's too high"
or "that's too low" until the player finally guesses the secret number.

1. Figure out how to generate a random number within a given range of values.
2. Create a main function that processes one guess from the player, and provides hints.
3. Add what we need to allow for multiple guesses until the player guesses the number. */

#include <cstdlib>  // rand, srand, argv
#include <ctime>    // time
#include <ctype.h>  // isdigit
#include <iostream>
#include <limits>   // std:numeric_limits
#include <string>   // std::stoi

// Prototypes
int generate_secret_number(int limit=100);
bool str_isdigit(char *str);

int main(int argc, char *argv[])
{
    // Number generator and argument check phase
    int number; // Secret number
    int limit;  // The number generated will be from 1 to limit

    // If a number is provided in argv[1], assign as limit
    if (argc > 1 && str_isdigit(argv[1]))
        limit = std::atoi(argv[1]);
    else
        limit = 100;

    number = generate_secret_number(limit);
    int guess = 0;  // Initialize guess var

    // Guessing game phase
    std::cout << "Guess the secret number (1 to " << limit << ")!" << std::endl;

    do
    {
        std::cout << "Number (-1 = quit): ";

        // Check for errors in input stream 
        if (!(std::cin >> guess))
        {
            // Clear error flag
            std::cin.clear();

            // Ignore all the characters in the input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << "Invalid input. Only integers are allowed." << std::endl;
        }
        else if (guess == -1)
            break;
        else if (guess < number)
            std::cout << "That's too low." << std::endl;
        else if (guess > number)
            std::cout << "That's too high." << std::endl;
        else
        {
            std::cout << "JACKPOT!\n";
            break;
        }
    } while (1);

    std::cout << number << " was the secret number." << std::endl;
    return 0;
}

// Return a "random" number between 1 and limit inclusive
int generate_secret_number(int limit)
{
    /* Seed the random number generator
    using the current running time in seconds */

    srand(time(nullptr));
    // Return number generated using rand()
    return rand() % limit + 1;
}

// Same as isdigit but for strings
bool str_isdigit(char *str)
{
    for (char* p = str; *p; p++)
    {
        if (!isdigit(*p))
            return false;
    }
    return true;
}