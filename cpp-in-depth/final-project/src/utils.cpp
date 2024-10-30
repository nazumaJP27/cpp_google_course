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

// Constructor 
HashTable::HashTable(unsigned int size) : table_(new node*[size]), size_(size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        table_[i] = nullptr;
    }
}

// Destructor
HashTable::~HashTable()
{
    node *curr = nullptr;
    node *temp = nullptr;
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
    unsigned int index = 1;

    for (char c : key)
    {
        index = (index * c) % size_;
    }
    return index;
}

void HashTable::insert(const std::string &in_word, const int &in_position)
{
    if (is_stop_word(in_word))
    {
        return;
    }

    unsigned int key = hash(in_word);

    if (table_[key] == nullptr)
    {
        table_[key] = new node(in_word, in_position);
    }
    else
    {
        node *cursor = table_[key];
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
            cursor->next = new node(in_word, in_position);
        }
    }
}

// Returns a nullpr if word not in hash table
node *HashTable::find(const std::string &in_word) const
{
    std::string word = normalize(in_word);
    unsigned int key = hash(word);
    node *cursor = table_[key];

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