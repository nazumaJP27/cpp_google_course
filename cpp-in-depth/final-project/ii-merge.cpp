// Test function for practicing the "merge" in two posting lists

#include <iostream>
#include <vector>

// Posting lists containg the DocIDs for each of the appearances of Brutus/Caesar
std::vector<int> brutus = { 2, 4, 8, 16, 32, 64, 128 };
std::vector<int> caesar = { 1, 2, 3, 5, 8, 13, 21, 34 };

// Merge function that finds the intersection of two posting lists and return a vector with the results
std::vector<int>* merge(std::vector<int>& postings0, std::vector<int>& postings1)
{
    std::vector<int> *merge_postings = new std::vector<int>;
    int len_postings0 = postings0.size();
    int len_postings1 = postings1.size();
    int cursor0 = 0, cursor1 = 0;

    while (cursor0 < len_postings0 && cursor1 < len_postings1)
    {
        if (postings0[cursor0] == postings1[cursor1])
        {
            merge_postings->push_back(postings0[cursor0]);
            ++cursor0;
            ++cursor1;
        }
        else
            (postings0[cursor0] > postings1[cursor1]) ? ++cursor1 : ++cursor0;
    }
    return merge_postings;
}

int main()
{
    // Use the merge funtion to find the DocIDs which contain Brutus and Caesar
    std::vector<int> *merged = merge(brutus, caesar);

    // Print the values in the merged vector, one per line
    for (int i : *merged)
        std::cout << i << '\n';
    
    delete merged;
}