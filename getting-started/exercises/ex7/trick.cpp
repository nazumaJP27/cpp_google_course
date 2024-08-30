/* Exercise 5: Number trick.
This is a number analogy to a famous card trick.
Example run:
---------------------------------------------
Before the algorithm: 789
After the algotithm:  789
---------------------------------------------
STEPS:
1. Ask the user to enter a three-digit number.
Think of the number as ABC (where A, B, C are the three digits of the number).
2. Now, find the remainders of the numbers formed by ABC, BCA, and CAB when divided by 11.
We will call these remainders X, Y, Z.
3. Add them up as X+Y, Y+Z, Z+X.
4. If any of the sums are odd, increase or decrease it by 11
(whichever operation results in a positive number less than 20;
note if the sum is 9, just report this and stop the process).
5. Finally, divide each of the sums in half. The resulting digits are A, B, C. 
TODO:
Write a program that implements this algorithm.*/

#include <iostream>
#include <limits>   // std::numeric_limits
#include <string>

bool SUM_NINE_FAIL = false;

struct Remainders {
    int x;
    int y;
    int z;
};

struct Sums {
    int XplusY;
    int YplusZ;
    int ZplusX;
    int a = 9;
};

// Prototypes
int get_three_digit_number(const std::string &prompt="Number: ");
Remainders calculate_remainders(const int &abc);
Sums calculate_sums(const Remainders &remainders);
void check_sums(Sums &sums);
void divide_sums(Sums &sums);

int main()
{
    // 1. Prompt for a three-digit number
    std::cout << "Enter a three-digit number." << std::endl;
    int abc = get_three_digit_number();

    // Display the three-digit number BEFORE running the algorithm
    std::cout << "\n---------------------------------\n"
              << "TRICK:\nBefore the algorithm process: " << abc << std::endl;

    // 2. Calculate the remainders of ABC, BCA, and CAB % 11
    Remainders remainders = calculate_remainders(abc);

    // 3. Sum the remainders as X+Y, Y+Z, Z+X 
    Sums sums = calculate_sums(remainders);

    // 4. Check if any of the sums are odd and add/subtract 11 accordingly
    check_sums(sums);

    if (SUM_NINE_FAIL == false)
    {
        // 5. Divide each of the sums in half
        divide_sums(sums);

        // Display the three-digit number AFTER the algorithm
        std::cout << "After the algorithm process:  "
                  << sums.XplusY << sums.YplusZ << sums.ZplusX << std::endl
                  << "---------------------------------\n"
                  << "PROCESS SUCCEEDED!\n";
    }
    else
        std::cout << "The process has failed...\n"
                  << "---------------------------------\n"
                  << "PROCESS FAILED, BUT DON'T WORRY! TRY ANOTHER NUMBER.\n"
                  << "\n-------------------------------------------\n"
                  << "REPORT:\nOne of the remainder sums had a value of 9.\n"
                  << "The algorithm can not proceed.\n"
                  << "-------------------------------------------\n";

    std::cout << "\nAll done.\n";
    return 0;
}

// Prompt [custom prompt] in a loop, validate and return input (step #1)
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

// Rearange the three-digit input number using integer arithmetic and return a struct
// with the remainders of the input, BCA, and CAB divided by 11 (step #2)
Remainders calculate_remainders(const int &abc)
{
    // Create BCA int variable with its corresponding digit order
    int bca = ((abc / 10) % 10) * 100; // B
    bca += (abc % 10) * 10;            // C
    bca += (abc / 100);                // A

    // Create CAB int variable in the same logic
    int cab = (abc % 10) * 100;        // C
    cab += (abc / 100) * 10;           // A
    cab += (abc / 10) % 10;            // B

    return {abc % 11, bca % 11, cab % 11};
}

// Add the remainders together and return a struct with the three possible sums (step #3)
Sums calculate_sums(const Remainders &remainders)
{
    return {
        remainders.x + remainders.y,
        remainders.y + remainders.z,
        remainders.z + remainders.x
    };
}

// Check sums for odd numbers and add/subtract 11 accordingly (step #4)
void check_sums(Sums &sums)
{
    auto adjust_sum = [](int &sum) -> void {
        if (sum == 9)
        {
            SUM_NINE_FAIL = true;
            return;
        }
        else if (sum % 2) // if the sum is odd
        {
            if ((sum + 11) < 20)
                sum += 11;
            else
                sum -= 11;
        }
    };

    adjust_sum(sums.XplusY);
    adjust_sum(sums.YplusZ);
    adjust_sum(sums.ZplusX);
    adjust_sum(sums.a);
}

// Divide all the sums in half (step #5)
void divide_sums(Sums &sums)
{
    sums.XplusY /= 2;
    sums.YplusZ /= 2;
    sums.ZplusX /= 2;
}