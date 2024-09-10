#pragma once

#include "Composer.h"
#include <algorithm>  // std::equal, std::sort
#include <cctype>     // std::tolower
#include <string>
#include <iomanip>    // std::setw
#include <iostream>
#include <vector>

const unsigned int MAX_COMPOSERS = 100;

class Database
{
    Composer composers_[MAX_COMPOSERS];
    int next_slot_;
    int rankw_, namew_, yobw_, genrew_; // Variables used for std::setw in composer_table()

public:
    // Constructor
    Database() : next_slot_(0), rankw_(7), namew_(40), yobw_(7), genrew_(17) {}

    // Methods 
    Composer& add_composer(const std::string &in_first_name, const std::string &in_last_name, int in_yob,
                           const std::string &in_genre, const std::string &in_fact);
    Composer* get_composer(const std::string &in_last_name);
    void display_all();
    void display_by_rank();
    void composer_table();
};
