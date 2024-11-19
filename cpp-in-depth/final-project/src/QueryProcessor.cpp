#include "../include/QueryProcessor.h"

std::string QueryProcessor::normalize(const std::string &in_word)
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

bool QueryProcessor::is_stop_word(const std::string &in_word)
{
    return stop_words.find(in_word) != stop_words.end();
}

// Merge function that finds the intersection of two posting lists and return a vector with the results
std::vector<int> QueryProcessor::merge_and(const std::vector<int>& postings0, const std::vector<int>& postings1)
{
    std::vector<int> merged_postings;
    int len_postings0 = postings0.size();
    int len_postings1 = postings1.size();
    int cursor0 = 0, cursor1 = 0;

    while (cursor0 < len_postings0 && cursor1 < len_postings1)
    {
        if (postings0[cursor0] == postings1[cursor1])
        {
            merged_postings.push_back(postings0[cursor0]);
            ++cursor0;
            ++cursor1;
        }
        else
            (postings0[cursor0] > postings1[cursor1]) ? ++cursor1 : ++cursor0;
    }
    return merged_postings;
}

// Merge function that returns two posting lists combined into one vector
std::vector<int> QueryProcessor::merge_or(const std::vector<int>& postings0, const std::vector<int>& postings1)
{
    // Combine the vectors postings0 and postings1 into a single vector using std::merge (the vector must be sorted)
    std::vector<int> merged_postings;
    std::merge(postings0.begin(), postings0.end(), postings1.begin(), postings1.end(), std::back_inserter(merged_postings));

    // Remove duplicates
    int i = 1, len_merged_postings = merged_postings.size();
    while (i < len_merged_postings)
    {
        if (merged_postings[i] == merged_postings[i - 1])
        {
            merged_postings.erase(merged_postings.begin() + i);
            len_merged_postings = merged_postings.size();
        }
        else
        {
            ++i;
        }
    }

    return merged_postings;
}

// Remove documents with terms that should be excluded (postings0 NOT postings1)
std::vector<int> QueryProcessor::merge_not(const std::vector<int>& postings0, const std::vector<int>& postings1)
{
    std::vector<int> merged_postings;
    int len_postings0 = postings0.size();
    int len_postings1 = postings1.size();
    int cursor0 = 0, cursor1 = 0;

    while (cursor0 < len_postings0 && cursor1 < len_postings1)
    {
        if (postings0[cursor0] < postings1[cursor1])
        {
            merged_postings.push_back(postings0[cursor0]);
            ++cursor0;
        }
        else
        {
            (postings0[cursor0] > postings1[cursor1]) ? ++cursor1 : (++cursor0, ++cursor1);
        }
    }

    // If there's more elements in postings0, insert them into the merged_postings vector
    if (cursor0 < len_postings0)
    {
        std::copy(postings0.begin() + cursor0, postings0.end(), std::back_inserter(merged_postings));
    }

    return merged_postings;
}