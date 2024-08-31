/*
TODO: Clear the error with cin.clear().
Remove the incorrect characters from the stream. 
One way to do this is with cin.ignore().

Description: Illustrate the use of cin to get input
and how to recover from errors.
*/

#include <iostream>
#include <limits>

int main()
{
    int input_var = 0;

    do
    {
        std::cout << "Enter a number (-1 = quit): ";

        if (!(std::cin >> input_var))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You entered a non-numeric. Only integers are allowed." << '\n';
        }
        else if (input_var != -1)
            std::cout << "You entered " << input_var << '\n';
    } while (input_var != -1);

    std::cout << "All done.\n";

    return 0;
}