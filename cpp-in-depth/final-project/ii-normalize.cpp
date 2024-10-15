// Test function to normalize words in text files

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

// Convert to lowercase and remove ponctuation
std::string normalize(const std::string &in_word)
{
    std::string out_word;
    for (char c : in_word)
    {
        if (std::isalnum(c))
            out_word.push_back(std::tolower(c));
    }
    return out_word;
}

int main()
{
    std::ifstream file("test-books/TREASURE ISLAND.txt");
    if (!file)
        return 1;
    else
    {
        std::string line;
        std::string word;
        while (std::getline(file, line))
        {
            std::istringstream line_stream(line);
            while (line_stream >> word)
            {
                std::cout << normalize(word) << '\n';
            }
        }
    }
}