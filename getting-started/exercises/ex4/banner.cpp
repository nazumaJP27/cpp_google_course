/* Exercise 4: Banner with big letters.
Print a banner for the following:
"EASY PEASY LEMON SQUEEZY"
We want the letters to be pretty big since this is a banner.
Example run:
---------------------------------------------
FFFFF
F
FFF
F
F

EEEEEE
E
EEEE
E
EEEEEE
---------------------------------------------
etc.

Rather than put all the cout's in the main function,
it would be far more efficient to put them in functions.
So we could have a "printE" function and a "printZ" function and so on.
TODO:
Write a program with functions that creates a banner
of a word or phrase with lots of repeated letters. */

#include <iostream>

// Prototypes
void printA(void);
void printE(void);
void printL(void);
void printM(void);
void printN(void);
void printO(void);
void printP(void);
void printQ(void);
void printS(void);
void printU(void);
void printY(void);
void printZ(void);

int main()
{
    std::cout << "\n\n";
    // EASY
    printE();
    printA();
    printS();
    printY();
    std::cout << "\n\n";
    // PEASY
    printP();
    printE();
    printA();
    printS();
    printY();
    std::cout << "\n\n";
    // LEMON
    printL();
    printE();
    printM();
    printO();
    printN();
    std::cout << "\n\n";
    // SQUEESY
    printS();
    printQ();
    printU();
    printE();
    printE();
    printZ();
    printY();
    std::cout << "Here's your \"EASY PEASY LEMON SQUEEZY\" banner!" << std::endl;

    return 0;
}

void printA()
{
    std::cout << "  A\n";
    std::cout << " A A \n";
    std::cout << "A   A \n";
    std::cout << "AAAAA\n";
    std::cout << "A   A\n" <<std::endl;
}

void printE()
{
    std::cout << "EEEEE\n";
    std::cout << "E\n";
    std::cout << "EEE\n";
    std::cout << "E\n";
    std::cout << "EEEEE\n" << std::endl;
}

void printL()
{
    std::cout << "L\n";
    std::cout << "L\n";
    std::cout << "L\n";
    std::cout << "L\n";
    std::cout << "LLLLL\n" << std::endl;
}

void printM()
{
    std::cout << "M   M\n";
    std::cout << "MM MM\n";
    std::cout << "M M M\n";
    std::cout << "M   M\n";
    std::cout << "M   M\n" << std::endl;
}

void printN()
{
    std::cout << "N   N\n";
    std::cout << "NN  N\n";
    std::cout << "N N N\n";
    std::cout << "N  NN\n";
    std::cout << "N   N\n" << std::endl;
}

void printO()
{
    std::cout << " OOO \n";
    std::cout << "O   O\n";
    std::cout << "O   O\n";
    std::cout << "O   O\n";
    std::cout << " OOO\n" << std::endl;
}

void printP()
{
    std::cout << "PPPPP\n";
    std::cout << "P   P\n";
    std::cout << "PPPP\n";
    std::cout << "P\n";
    std::cout << "P\n" << std::endl;
}

void printQ()
{
    std::cout << " QQQ\n";
    std::cout << "Q   Q\n";
    std::cout << "Q   Q\n";
    std::cout << "Q Q Q\n";
    std::cout << " QQQ\n";
    std::cout << "    Q\n" << std::endl;
}

void printS()
{
    std::cout << " SSSS\n";
    std::cout << "S\n";
    std::cout << " SSS\n";
    std::cout << "    S\n";
    std::cout << "SSSS\n" << std::endl;
}

void printU()
{
    std::cout << "U   U\n";
    std::cout << "U   U\n";
    std::cout << "U   U\n";
    std::cout << "U   U\n";
    std::cout << " UUU\n" << std::endl;
}

void printY()
{
    std::cout << "Y   Y\n";
    std::cout << " Y Y\n";
    std::cout << "  Y\n";
    std::cout << "  Y\n";
    std::cout << "  Y\n" << std::endl;
}

void printZ()
{
    std::cout << "ZZZZZ\n";
    std::cout << "   Z\n";
    std::cout << "  Z\n";
    std::cout << " Z\n";
    std::cout << "ZZZZZ\n" << std::endl;
}