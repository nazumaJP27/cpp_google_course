#include "../include/InvertedIndex.h"

// Constructor
InvertedIndex::InvertedIndex(const std::string &in_docs_path=DEFAULT_DOCS_PATH) : docs_path_(in_docs_path)
{
    // Iterate over the files in the doc_path and create Document objects
    for (const auto &file : std::filesystem::directory_iterator(docs_path_))
    {
        if (file.is_regular_file() && file.path().extension() == ".txt")
        {
            Document *doc = new Document(file.path().string());
            documents_.emplace_back(doc);
        }
    }

    for (const Document *doc : documents_)
    {
        add_document(*doc);
    }
}

// Destructor
InvertedIndex::~InvertedIndex()
{
    for (const Document *doc : documents_)
    {
        delete doc;
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