#pragma once

#include <algorithm>     // std::merge
#include <iostream>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>

// Stop-words
static const std::unordered_set<std::string> stop_words {"a", "and", "if", "in", "of", "or", "so", "the"};
const unsigned int TERM_MAX_LENGTH = 50;

class QueryProcessor
{
    friend class InvertedIndex;

    // QueryToken struct
    enum QueryOperator { AND, OR, NOT, NONE };

    struct QueryToken
    {
        const std::string term;
        QueryOperator op;

        // QueryToken constructor
        QueryToken(const std::string& in_term, QueryOperator in_op=NONE) : term(in_term), op(in_op) {}
    };

public:
    // Methods
    static bool is_stop_word(const std::string &in_word);
    static std::string normalize(const std::string &in_word);

    std::vector<QueryToken> parse_query(const std::string& in_query) const;

    // Merge operator functions (AND - OR - NOT)
    std::vector<int> merge_and(const std::vector<int>& postings0, const std::vector<int>& postings1);
    std::vector<int> merge_or(const std::vector<int>& postings0, const std::vector<int>& postings1);
    std::vector<int> merge_not(const std::vector<int>& postings0, const std::vector<int>& postings1);
};