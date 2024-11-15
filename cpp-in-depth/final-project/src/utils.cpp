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

bool is_stop_word(const std::string &in_word)
{
    return stop_words.find(in_word) != stop_words.end();
}

// Merge function that finds the intersection of two posting lists and return a vector with the results
std::vector<int> merge_and(const std::vector<int>& postings0, const std::vector<int>& postings1)
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
std::vector<int> merge_or(const std::vector<int>& postings0, const std::vector<int>& postings1)
{
    std::vector<int> merged_postings;
    std::merge(postings0.begin(), postings0.end(), postings1.begin(), postings1.end(), std::back_inserter(merged_postings));

    // Remove duplicates
    int i = 1;
    while (i < merged_postings.size())
    {
        if (merged_postings[i] == merged_postings[i - 1])
        {
            merged_postings.erase(merged_postings.begin() + i);
        }
        else
        {
            ++i;
        }
    }

    return merged_postings;
}

// HashTable ::
// Constructor 
HashTable::HashTable(unsigned int size) : table_(new TermNode*[size]), size_(size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        table_[i] = nullptr;
    }
}

// Destructor
HashTable::~HashTable()
{
    TermNode *curr = nullptr;
    TermNode *temp = nullptr;
    for (unsigned int i = 0; i < size_; ++i)
    {
        curr = table_[i];
        while (curr != nullptr)
        {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete [] table_;
}

const unsigned int HashTable::hash(const std::string &key) const
{
    return std::hash<std::string>{}(key) % size_;
}

void HashTable::insert(const std::string &in_word, const int &in_position) const
{
    if (in_word.length() > TERM_MAX_LENGTH || in_word.empty() || is_stop_word(in_word))
    {
        return;
    }

    unsigned int key = hash(in_word);

    if (table_[key] == nullptr)
    {
        table_[key] = new TermNode(in_word, in_position);
    }
    else
    {
        TermNode *cursor = table_[key];
        while(cursor->word != in_word && cursor->next != nullptr)
        {
            cursor = cursor->next;
        }
        if (cursor->word == in_word)
        {
            cursor->info.frequence++;
            cursor->info.positions.push_back(in_position);
        }
        else
        {
            cursor->next = new TermNode(in_word, in_position);
        }
    }
}

// Returns a nullpr if word not in hash table
TermNode *HashTable::find(const std::string &in_word) const
{
    std::string word = normalize(in_word);
    unsigned int key = hash(word);
    TermNode *cursor = table_[key];

    if (cursor)
    {
        while (cursor->word != in_word)
        {
            cursor = cursor->next;
            if (!cursor)
            {
                // in_word not in table_
                break;
            }
        }
    }
    return cursor;
}