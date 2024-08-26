/* The greatest common divisor of two integers is the largest number that divides them both evenly.
For example, gcd(12, 18) = 6, gcd(−4, 14) = 2.
The most efficient way to compute gcd is with the Euclidean algorithm.
Write a program with a function to compute gcd for two integers.
Try doing the function without recursion first */

#include <ctype.h>  // isdigit
#include <iostream>
#include <string>   // std::atoi

// Prototypes
int euclidean_alg(int x, int y);
bool str_isdigit(char *str);

int main(int argc, char *argv[])
{
    if (argc == 3 && str_isdigit(argv[1]) && str_isdigit(argv[2]))
    {
        int x = std::stoi(argv[1]);
        int y = std::stoi(argv[2]);

        std::cout << "The greatest common divisor of " << x << " and " << y << " is "
                  << euclidean_alg(x, y) << ".\n";
        return 0;
    }
    else
    {
        std::cout << "Usage: gcd.exe integer0 integer1\n";
        return 1;
    }
}

// Same as isdigit but for strings
bool str_isdigit(char *str)
{
    for (char* p = str; *p; p++)
    {
        if (*p == '-')
            continue; // Skip the minus sign character
        else if (!isdigit(*p))
            return false;
    }
    return true;
}

// Function that returns the GCD of two integers using the Euclidean algorithm
int euclidean_alg(int x, int y)
{
    int tmp = 0;
    if (x < y)
    {
        tmp = x;
        x = y;
        y = tmp;
    }

    while (y)
    {
        tmp = y;
        y = x % y;
        x = tmp;
    }
    return x;
}