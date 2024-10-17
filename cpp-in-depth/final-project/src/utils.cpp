#include "../include/utils.h"

std::string normalize(const std::string &in_word)
{
    std::string out_word;
    for (char c : in_word)
    {
        if (std::isalpha(c))
        {
            out_word.push_back(std::tolower(c));
        }
    }
    return out_word;
}