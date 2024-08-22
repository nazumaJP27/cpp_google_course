/*
Using the program you just completed (hello1.cpp), figure out how to print "Hello, world!"
left-aligned in the fields of 17 spaces (the default is usually right-aligned)
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << setw(17) << left << "Hello, world!";
        cout << '\n';
    }

    return 0;
}