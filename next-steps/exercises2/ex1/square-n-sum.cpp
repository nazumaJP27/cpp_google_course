/* Exercise 1: Square 'N Sum.
The integer 36 has a peculiar property:
    It is a perfect square, and is also the sum of the integers from 1 through 8.
    The next such number is 1225 which is 35², and the sum of the integers from 1 through 49.
Example run:
---------------------------------------------
The number 41616 is a perfect square.
It is the sum of the integers 1 through 288.
---------------------------------------------
TODO:
Find the next number that is a perfect square and also the sum of a series 1...n. This next number may be greater than 32767.
You may use library functions that you know of, (or mathematical formulas) to make your program run faster. */

#include <iostream>
#include <math.h>   // sqrt

// Constants 
const unsigned int START_N = 9;  // Starting point in the loop used to find the sum of a series (1-49 = 1225)

// Prototypes
bool perfect_square(const int x);
int sum_series(const int n);

int main()
{
    int n = START_N, number = 0;

    // Loop until the sum of the integers 1 through n is a perfect square
    while (1)
    {
        number = sum_series(n);
        if (perfect_square(number))
        {
            // Display the number and break from the loop
            std::cout << "The number " << number << " is a perfect square.\n" 
                      << "It is the sum of the integers 1 through " << n << ".\n";
            break;
        }
        ++n;
    }
    return 0;
}

// Check if x is a perfect square
bool perfect_square(const int x)
{
    // Truncate the square root of x
    int root = sqrt(x);
    // Return true/false by squaring the truncated root of x
    return (root * root == x);
}

// This formula returns the sum of the integers from 1 through n
int sum_series(const int n)
{
    return n * (n + 1) / 2;
}