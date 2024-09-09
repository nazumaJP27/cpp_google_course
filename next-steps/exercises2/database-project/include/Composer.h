#pragma once

#include <algorithm>
#include <iostream>
#include <string>

const unsigned int MAX_RANK = 10;
const unsigned int DEFAULT_RANK = 0;

class Composer
{
    std::string first_name_;
    std::string last_name_;
    int yob_;           // year of birth
    std::string genre_; // baroque, classical, romantic
    std::string fact_;
    unsigned int ranking_;

public:
    // Constructors
    Composer(const std::string &in_first_name, const std::string &in_last_name, int in_yob,
             const std::string &in_genre, const std::string &in_fact, unsigned int in_ranking=DEFAULT_RANK);
    Composer();

    // Accessors and Mutators
    void set_first_name(const std::string &in_first_name) { first_name_ = in_first_name; }
    const std::string &get_first_name() const { return first_name_; }

    void set_last_name(const std::string &in_last_name) { last_name_ = in_last_name; }
    const std::string &get_last_name() const { return last_name_; }

    void set_yob(int in_yob) { yob_ = in_yob; }
    int get_yob() const { return yob_; }

    void set_genre(const std::string &in_genre) { genre_ = in_genre; }
    const std::string &get_genre() const { return genre_; }

    void set_fact(const std::string &in_fact) { fact_ = in_fact; }
    const std::string &get_fact() const { return fact_; }

    void set_ranking(unsigned int in_ranking);
    unsigned int get_ranking() const { return ranking_; }

    // Methods
    void display();
    void promote(unsigned int increment=1) { ranking_ = std::min(MAX_RANK, ranking_ + increment); }
    void demote(unsigned int decrement=1) { ranking_ = std::max(DEFAULT_RANK, ranking_ - decrement); }
};



