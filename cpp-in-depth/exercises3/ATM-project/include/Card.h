#pragma once

#include <string>

class Card
{
    const std::string number_;
    const std::string flag_;

public:
    // Constructor
    Card(std::string number, std::string flag) : number_(number), flag_(flag){}

    std::string get_card_number() const { return number_; }
    std::string get_card_flag() const { return flag_; }
};