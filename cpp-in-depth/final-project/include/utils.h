#pragma once

#include <string>
#include <unordered_set>
#include <vector>

// Constants
const unsigned int HT_DEFAULT_SIZE = 27017;
const unsigned int TERM_MAX_LENGTH = 50;

// Stop-words
const std::unordered_set<std::string> stop_words({"a", "and", "if", "in", "of", "or", "so", "the"});

// Functions
bool is_stop_word(const std::string &in_word);
std::string normalize(const std::string &in_word);

// HashTable ::
struct TermNode
{
    struct TermInfo
    {
        int frequence = 0;
        std::vector<int> positions;

        TermInfo(const int in_frequence=1, const int in_position=0) : frequence(in_frequence), positions({in_position}) {}
    };

    std::string word;
    TermInfo info;
    TermNode *next;

    TermNode(const std::string &in_word, const int in_position, const int in_frequence=1) : word(in_word), info(in_frequence, in_position), next(nullptr) {}
};

struct HashTable
{
    TermNode **table_;
    const unsigned int size_;

    // Constructor
    HashTable(unsigned int size=HT_DEFAULT_SIZE);
    ~HashTable();

    const unsigned int hash(const std::string &key) const;
    void insert(const std::string &in_word, const int &in_position=0) const;
    TermNode *find(const std::string &in_word) const;

    // Accessors
    const TermNode* const *get_table() const { return table_; }
    const unsigned int get_size() const { return size_; }
};
