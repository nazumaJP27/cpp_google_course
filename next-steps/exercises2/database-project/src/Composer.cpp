#include "../include/Composer.h"

// Constructor with arguments
Composer::Composer(const std::string &in_first_name, const std::string &in_last_name, int in_yob,
             const std::string &in_genre, const std::string &in_fact, unsigned int in_ranking) : 
             first_name_(in_first_name), last_name_(in_last_name), yob_(in_yob), genre_(in_genre), fact_(in_fact), ranking_(in_ranking) {}

// Constructor without arguments
Composer::Composer() : first_name_(""), last_name_(""), yob_(0), genre_(""), fact_(""), ranking_(0) {}

// Display info of the composer into console
void Composer::display()
{
    std::cout << get_first_name() << " " << get_last_name() << std::endl;
}

// Check bounds and set ranking
void Composer::set_ranking(int in_ranking)
{
    if (in_ranking >= DEFAULT_RANK && in_ranking <= MAX_RANK)
        ranking_ = in_ranking;
    else
        ranking_ = DEFAULT_RANK;
}