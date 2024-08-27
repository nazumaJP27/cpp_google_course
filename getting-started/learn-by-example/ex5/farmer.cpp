/* One of the powers of computing is being able to do a brute-force search for a solution to a problem.
Trial and error works just fine for some problems.
In fact, computers can be especially good at such problems. Consider this:

Horses cost $10, pigs cost $3, and rabbits are only $0.50.
A farmer buys 100 animals for $100. How many of each animal did he buy? 
There is a remarkably simple solution to this problem. */

#include <iostream>

int main()
{
    float rabbit_value = 0.5, pig_value = 3, horse_value = 10;

    std::cout << "\nA farmer wants to buy 100 animals total.\n" << "How many of each animal he can buy with $100?\n" << std::endl;
    for (int rabbit = 0; rabbit < 100; rabbit++)
        for (int pig = 0; pig < 100; pig++)
            for (int horse = 0; horse < 100; horse++)
                if ((rabbit + pig + horse) == 100)
                    if ((rabbit * rabbit_value) + (pig * pig_value) + (horse * horse_value) == 100)
                        std::cout << rabbit << " rabbits, " << pig << " pigs, and " << horse << " horses.\n";

    return 0;
}