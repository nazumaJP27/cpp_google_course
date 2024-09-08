#include "../include/Database.h"

Composer& Database::add_composer(const std::string &in_first_name, const std::string &in_last_name, int in_yob,
                                 const std::string &in_genre, const std::string &in_fact)
{
    // Instantiate a Composer object
    Composer new_composer(in_first_name, in_last_name, in_yob, in_genre, in_fact);

    // Add the object to the array of composers
    composers_[next_slot_] = new_composer;

    // Return a reference to the newly added composer and then increment next_slot_
    return composers_[next_slot_++];
}

// Check the array of composers and compare (case-insensitively) their last name with the input argument
// Return a pointer to the matching Composer object or a nullptr
Composer* Database::get_composer(const std::string &in_last_name)
{
    // Case-insentive comparison lambda
    auto nocase_compare = [](const std::string &str0, const std::string &str1) -> bool
    {
        if (str0.size() != str1.size()) return false;
        return std::equal(str0.begin(), str0.end(), str1.begin(),
                          [](char c0, char c1) { return std::tolower(c0) == std::tolower(c1); });
    };

    // Composer search
    for (int i = 0; i < next_slot_; ++i)
    {
        if (nocase_compare(in_last_name, composers_[i].get_last_name()))
            return &composers_[i];
    }
    return nullptr;
}

void Database::display_all()
{
    std::cout << "Rank\tName\t\t\tBorn\tGenre\t\tFact\n\n";
    for (int i = 0; i < next_slot_; ++i)
    {
        std::cout << composers_[i].get_ranking() << '\t'
                  << composers_[i].get_first_name() << ' ' << composers_[i].get_last_name()
                  << "\t\t" << composers_[i].get_yob() << '\t' << composers_[i].get_genre()
                  << "\t\t" << composers_[i].get_fact() << '\n';
    }
    std::cout << std::endl;
}

void Database::display_by_rank()
{
    // Create a vector of pointers to the valid range of Composer objects from composers_
    std::vector<const Composer*> sorted_composers;
    for (int i = 0; i < next_slot_; ++i)
        sorted_composers.push_back(&composers_[i]);

    // Sort vector by the ranking of each composer
    std::sort(sorted_composers.begin(), sorted_composers.end(), [](const Composer *x, const Composer *y)
              { return x->get_ranking() > y->get_ranking(); });

    // Display composers from vector
    std::cout << "Rank\tName\t\t\tBorn\tGenre\t\tFact\n\n";
    for (const Composer *composer : sorted_composers)
    {
        std::cout << composer->get_ranking() << '\t'
                  << composer->get_first_name() << ' ' << composer->get_last_name()
                  << "\t\t" << composer->get_yob() << '\t' << composer->get_genre()
                  << "\t\t" << composer->get_fact() << '\n';
    }
    std::cout << std::endl;
}