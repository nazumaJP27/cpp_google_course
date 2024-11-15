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
        add_document_terms(*doc);
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

// Iterate over a Document object HashTable and add its terms to the instance HashTable ii_terms_ variable
void InvertedIndex::add_document_terms(const Document &in_doc) const
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

// Tokenize and merge query terms, then returns a vector with the document IDs 
const std::vector<int> InvertedIndex::process_query(const std::string &in_query)
{
    // Tokenize the query and get TermNode pointers for each term
    std::vector<const TermNode*> query_terms = tokenize_query(in_query);
    int len_query_terms = query_terms.size();

    if (len_query_terms < 1)
    {
        // No terms found in the query
        return {};
    }

    // If there is only one term, return its document positions directly
    if (len_query_terms == 1)
    {
        return query_terms[0]->info.positions;
    }

    // Initialize possible_doc_ids with the postings list of the first term
    std::vector<int> possible_doc_ids = query_terms[0]->info.positions;

    // Merge each subsequent term's posting list with possible_doc_ids
    for (int i = 1; i < len_query_terms; ++i)
    {
        const std::vector<int> &postings = query_terms[i]->info.positions;

        if (possible_doc_ids.size())
        {
            possible_doc_ids = merge_and(possible_doc_ids, postings);
        }
        else
        {
            // If the merged result is empty, no further processing is needed
            break;
        }
    }

    return possible_doc_ids;
}

// Tokenize query and return its terms into a vector
std::vector<const TermNode*> InvertedIndex::tokenize_query(const std::string &in_query)
{
    std::stringstream query_stream(in_query);
    std::string word;
    const TermNode *curr_term;
    std::vector<const TermNode*> tokenized_query;

    while (query_stream >> word)
    {
        word = normalize(word);
        if (word.length() > TERM_MAX_LENGTH || word.empty() || is_stop_word(word))
        {
            std::cout << "Term \"" << word << "\" discarted from search...\n";
            continue;
        }
        else if ((curr_term = ii_terms_.find(word)))
        {
            tokenized_query.push_back(curr_term);
        }
        else
        {
            std::cout << "Term \"" << word << "\" not found in the Inverted Index...\n";
        }
    }

    if (tokenized_query.size() > 1)
    {
        // Sort TermNodes in the vector by frequence in ascendig order and return
        std::sort(tokenized_query.begin(), tokenized_query.end(), [](const TermNode* a, const TermNode* b)
        { return a->info.frequence < b->info.frequence; });
    }

    return tokenized_query;
}