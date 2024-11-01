#include "../include/InvertedIndex.h"

// Default constructor
InvertedIndex::InvertedIndex() {}

// Constructor
InvertedIndex::InvertedIndex(const std::vector<Document*> &in_documents)
{
    for (Document *doc : in_documents)
    {
        add_document(*doc);
    }
}

void InvertedIndex::add_document(const Document &in_doc) const
{
    const int doc_id = in_doc.get_doc_id();
    const TermNode* const *doc_terms_table = in_doc.get_terms().get_table();
    const unsigned int doc_table_size = in_doc.get_terms().get_size();

    const TermNode *cursor = doc_terms_table[0];
    for (unsigned int i = 0; i < doc_table_size - 1; ++i, cursor = doc_terms_table[i])
    {
        while (cursor)
        {
            ii_terms_.insert(cursor->word, doc_id);
            cursor = cursor->next;
        }
    }
}