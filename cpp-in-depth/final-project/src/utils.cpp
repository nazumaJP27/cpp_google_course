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

const unsigned int HashTable::hash(const std::string &key)
{
    unsigned int index = 1;

    for (char c : key)
    {
        index = (index * c) % size_;
    }
    return index;
}

void HashTable::insert(const std::string &in_word)
{
    unsigned int key = hash(in_word);
 
    node *new_node = new node;
    new_node->next = nullptr;
    new_node->word = in_word;

    if (table_[key] == nullptr)
    {
        table_[key] = new_node;
    }
    else
    {
        node *cursor = table_[key];
        while (cursor->next != nullptr)
        {
            cursor = cursor->next;
        }
        cursor->next = new_node;
    }
}

// Returns a nullpr if word not in hash table
node *HashTable::find(const std::string &in_word)
{
    unsigned int key = hash(in_word);
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