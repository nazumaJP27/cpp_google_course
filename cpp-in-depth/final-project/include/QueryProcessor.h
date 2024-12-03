#pragma once

#include "utils.h"

#include <algorithm>     // std::merge
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

class QueryProcessor
{
    friend class InvertedIndex;

    // QueryToken struct

    enum QueryOperator { AND, OR, NOT };
    enum TokenType { NORMAL, PHRASE, PHRASE_END };

    struct QueryToken
    {
        std::string term;
        QueryOperator op;
        TokenType type;

        // QueryToken constructor
        QueryToken(const std::string& in_term, QueryOperator in_op, TokenType in_type) : term(in_term), op(in_op), type(in_type) {}

        // Constructor for invalid terms inside phrase queries only
        // This terms will be ignored by the Inverted Index, and will only be used to match positions in the InvertedIndex::phrase_in_document method
        QueryToken(QueryOperator in_op, TokenType in_type=PHRASE) : term(), op(in_op), type(in_type) {}
        
        bool is_phrase_stop_word() { return (type == PHRASE || type == PHRASE_END) && term.empty(); }
    };

public:
    std::vector<QueryToken> parse_query(const std::string& in_query) const;

    // Merge operator functions (AND - OR - NOT)
    std::vector<int> merge_and(const std::vector<int>& postings0, const std::vector<int>& postings1);
    std::vector<int> merge_or(const std::vector<int>& postings0, const std::vector<int>& postings1);
    std::vector<int> merge_not(const std::vector<int>& postings0, const std::vector<int>& postings1);
};