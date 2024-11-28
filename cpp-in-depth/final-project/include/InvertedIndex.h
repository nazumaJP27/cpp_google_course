#pragma once

#include "Document.h"
#include "QueryProcessor.h"
#include "utils.h"

#include <filesystem>
#include <sstream>
#include <vector>

class InvertedIndex
{
    std::string docs_path_;
    std::vector<Document*> documents_;
    HashTable ii_terms_;
    QueryProcessor processor_;

public:
    // Costructor
    InvertedIndex(const std::string &in_docs_path);

    // Destructor
    ~InvertedIndex();

    // Methods
    const std::vector<int> process_query(const std::string &in_query);

    // Accessors
    const std::string& get_docs_path() const { return docs_path_; }
    const std::vector<Document*>& get_documents() const { return documents_; }

    const std::vector<int>* positions_in_document(const TermNode* in_term, int in_doc_id);

private:
    void add_document_terms(const Document &in_doc) const;
    std::vector<std::vector<int>> get_postings(std::vector<QueryProcessor::QueryToken>& in_query_tokens);
    std::vector<int> process_phrase(const std::vector<const TermNode*> in_phrase_terms);
    bool phrase_in_document(int doc_id, const std::vector<const TermNode*>& in_phrase_terms);
};