/*
Modify the `hello0.cpp` program to print "Hello, world!" 4 times on a line for 6 lines, 
where each is printed in a field of 17 spaces. Use for-loops to do this.
*/

#include <iostream>
#include <iomanip>      // std::setw
using namespace std;

int main()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << setw(17) << "Hello, world!";
        }
        cout << '\n';
    }
    return 0;
}