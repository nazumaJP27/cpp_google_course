#pragma once

#include <string>
#include <vector>

std::string normalize(const std::string &in_word);

// HashTable ::
const unsigned int HT_DEFAULT_SIZE = 2700;

struct TermInfo
    {
        int frequence = 0;
        std::vector<int> positions;

        //TermInfo(const int &in_frequence=1, const int &in_position=0) : frequence(in_frequence), positions(positions.push_back(in_position)) {}
    };

struct node
{
    std::string word;
    TermInfo info;
    node *next;

    node(const std::string &in_word) : word(in_word), next(nullptr) {}
};

struct HashTable
{
    node **table_;
    const unsigned int size_;

    // Constructor
    HashTable(unsigned int size=HT_DEFAULT_SIZE);
    ~HashTable();

    const unsigned int hash(const std::string &key);
    void insert(const std::string &in_word, const int &in_position=0);
    node *find(const std::string &in_word);
};
