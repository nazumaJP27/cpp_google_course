#pragma once

#include "Document.h"
#include "utils.h"

#include <algorithm>
#include <filesystem>
#include <sstream>
#include <vector>

class InvertedIndex
{
    std::string docs_path_;
    std::vector<Document*> documents_;
    HashTable ii_terms_;

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

private:
    void add_document(const Document &in_doc) const;
    std::vector<const TermNode*> tokenize_query(const std::string &in_query);
    std::vector<int> merge(const std::vector<int>& postings0, const std::vector<int>& postings1);
};