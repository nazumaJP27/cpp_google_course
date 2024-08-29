/* Exercise 6: Date decoder.
Example run:
---------------------------------------------
Encoded date: ARZM
Decoded date: 01/19/2008
---------------------------------------------

Nadine is a self-appointed Food Quality Spy. She has learned that many food product manufacturers
have started encoding the product expiration dates to keep customers from knowing how old the stuff is.
But the encoding does allow grocers to figure out the expiration dates if for some reason, they want to.

One popular encoding method:
1. Encode the months from Jan to Dec as 'A' through 'L'
2. Encode each digit of the date as 'Q' through 'Z'
3. Encode the year as 'A' through 'Z' meaning 1 through 26 which is then added to 1995.
TODO:
Write a program to decode dates that are using this enconding method. */

#include <algorithm> // std::remove_if, std::transform
#include <iostream>
#include <limits>    // std::numeric_limits
#include <string>

// Constants for decoding
const unsigned BASE_DAY = 'Q';
const unsigned BASE_MONTH = 'A' - 1;
const unsigned BASE_YEAR = 1995;
const unsigned MAXIMUM_YEAR = BASE_YEAR + 'Z' + 1;

// Enum for decoded date
enum DateIndex {
    MONTH,
    DAY_FIRST_DIGIT,
    DAY_SECOND_DIGIT,
    YEAR
};

struct DecodedDate
{
    int month = 0;
    int day = 0;
    int year = 0;
    bool valid_date = false;
};

// Prototypes
void clean_string(std::string &str);
DecodedDate decode_date(std::string &str);
std::string get_encoded_date(const std::string &prompt="Date: ");

int main()
{
    // Prompt for encoded date
    std::string in_date = get_encoded_date("Enconded date: ");

    // Decode in_date and initialize a DecodedDate struct
    DecodedDate out_date = decode_date(in_date);

    if (out_date.valid_date)
        std::cout << "Decoded date: " << out_date.month << '/' << out_date.day << '/' << out_date.year << std::endl;
    else
        std::cout << "Invalid date";

    return 0;
}

// Prompt [custom prompt] in a loop, validate, and return input
std::string get_encoded_date(const std::string &prompt)
{
    std::string input;
    do
    {
        std::cout << prompt;
        std::cin >> input;
        // Remove '/' and '-' chars and remove them
        clean_string(input);
        if (input.length() != 4)
        {
            std::cout << "Invalid input. The encoded date should only have 4 characters." << std::endl;
            input.clear();
        }
        // Clear input buffer
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (input.empty());

    return input;
}

// Remove '/', '-', or '.' chars and upper case input string
void clean_string(std::string &input)
{
    std::string::iterator new_end = std::remove_if(input.begin(), input.end(), [](char c)
    { return c == '/' || c == '-' || c == '.' || c == ','; });
    input.erase(new_end, input.end());

    // Upper case all chars in string
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
}

// Decodes input string, validate, and return DecodedDate struct
DecodedDate decode_date(std::string &input)
{
    DecodedDate decoded;

    // Initialize variables with decoded values for month, day, and year
    int m = input[MONTH] - BASE_MONTH;
    int d = (input[DAY_FIRST_DIGIT] - BASE_DAY) * 10;
    d += (input[DAY_SECOND_DIGIT] - BASE_DAY);
    int y = (input[YEAR] - 'A' + 1) + BASE_YEAR;

    // Validate vars values
    if (m > 0 && m < 13 && d > 0 && d < 32 && y <= MAXIMUM_YEAR)
    {
        decoded.month = m;
        decoded.day = d;
        decoded.year = y;
        decoded.valid_date = true;
    }
    return decoded;
}