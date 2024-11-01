#pragma once

#include "Document.h"
#include "utils.h"
#include <vector>

class InvertedIndex
{
    HashTable ii_terms_;

public:
    // Costructor
    InvertedIndex();
    InvertedIndex(const std::vector<Document*> &in_documents);

    // Methods
    void add_document(const Document &in_doc) const;
};