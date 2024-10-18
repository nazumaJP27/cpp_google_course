#pragma once

#include <string>

std::string normalize(const std::string &in_word);

struct node
{
    std::string word;
    node *next;
};

struct HashTable
{
    node **table_;
    unsigned int size_;

    // Constructor
    HashTable(unsigned int size);
    ~HashTable();

    const unsigned int hash(const std::string &key);
    void insert(const std::string &in_word);
    node *find(const std::string &in_word);
};
