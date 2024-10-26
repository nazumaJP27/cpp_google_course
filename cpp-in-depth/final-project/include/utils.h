#pragma once

#include <string>
#include <unordered_set>
#include <vector>

std::string normalize(const std::string &in_word);

// Stop-words
const std::unordered_set<std::string> stop_words({"a", "and", "if", "in", "of", "or", "so", "the"});

bool is_stop_word(const std::string &in_word);

// HashTable ::
const unsigned int HT_DEFAULT_SIZE = 2700;

struct node
{
    struct TermInfo
    {
        int frequence = 0;
        std::vector<int> positions;

        TermInfo(const int &in_frequence=1, const int &in_position=0) : frequence(in_frequence), positions({in_position}) {}
    };

    std::string word;
    TermInfo info;
    node *next;

    node(const std::string &in_word, const int in_position, const int in_frequence=1) : word(in_word), info(in_frequence, in_position), next(nullptr) {}

};

struct HashTable
{
    node **table_;
    const unsigned int size_;

    // Constructor
    HashTable(unsigned int size=HT_DEFAULT_SIZE);
    ~HashTable();

    const unsigned int hash(const std::string &key) const;
    void insert(const std::string &in_word, const int &in_position=0);
    node *find(const std::string &in_word) const;
};
