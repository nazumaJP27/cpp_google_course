#include "../include/InvertedIndex.h"

// Constructor
InvertedIndex::InvertedIndex(const std::string &in_docs_path=DEFAULT_DOCS_PATH) : docs_path_(in_docs_path)
{
    // Iterate over the files in the docs_path and create Document objects
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
    for (unsigned int i = 0; i < doc_table_size - 1; cursor = doc_terms_table[++i])
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
    // Tokenize the query and parse for operators (AND, OR, NOT, PHRASE, PHRASE_END) for each term
    std::vector<QueryProcessor::QueryToken> query_tokens = processor_.parse_query(in_query);

    // Get postings for each term in the query and append to an index on the new vector, processing phrases ("phrase query") and ignoring invalid terms
    // Ignored terms are also erased from the query_tokens vector, so the indexes on both `query_tokens` and `postings` match ([token][postings])
    std::vector<std::vector<int>> postings = get_postings(query_tokens);

    int len_query_tokens = query_tokens.size(), len_postings = postings.size();

    if (len_query_tokens < 1 || len_postings < 1)
    {
        // No terms found in the query
        std::cout << "No valid terms in the query...\n";
        return {};
    }

    // Initialize possible_doc_ids with the postings list of the first term
    std::vector<int> possible_doc_ids = postings[0];

    int query_index = 0;

    // Merge each subsequent term's posting list with possible_doc_ids and apply operators
    while (++query_index < len_query_tokens)
    {
        const QueryProcessor::QueryToken& token = query_tokens[query_index];
        const std::vector<int> &token_postings = postings[query_index];

        // Apply the corresponding merge operator
        switch (token.op)
        {
            case QueryProcessor::OR:
                possible_doc_ids = processor_.merge_or(possible_doc_ids, token_postings);
                break;
            case QueryProcessor::NOT:
                possible_doc_ids = processor_.merge_not(possible_doc_ids, token_postings);
                break;
            case QueryProcessor::AND:
                possible_doc_ids = processor_.merge_and(possible_doc_ids, token_postings);
                break;
        }
    }

    return possible_doc_ids;
}

// Takes a vector of QueryToken objs and return a vector with the posting lists for each term found in the ii_terms_
std::vector<std::vector<int>> InvertedIndex::get_postings(std::vector<QueryProcessor::QueryToken>& in_query_tokens)
{
    std::vector<std::vector<int>> postings;

    // Instantiate a vector to store TermNode pointers to process phrase queries (ONLY USED IN PHRASE QUERIES AND POSITIONAL INDEXES)
    std::vector<const TermNode*> phrase_terms;

    size_t index = 0;
    QueryProcessor::QueryToken* curr_token;
    const TermNode* term_node;

    while (index < in_query_tokens.size())
    {
        curr_token = &in_query_tokens[index];

        if (curr_token->is_phrase_stop_word())
        {
            // Append a pointer to NULL representing a term to be ignored and only used for matching positions in phrase processing
            phrase_terms.push_back(nullptr);
            // Erase the token index from the in_query_tokens vector, as the phrase will get one posting list after processing
            in_query_tokens.erase(in_query_tokens.begin() + index);
            continue;
        }

        if (!(term_node = ii_terms_.find(curr_token->term)) )
        {
            std::cout << "Term \"" << curr_token->term << "\" excluded from the search because was not found in the Inverted Index...\n";
            in_query_tokens.erase(in_query_tokens.begin() + index);
            continue;
        }

        if (curr_token->type == QueryProcessor::PHRASE)
        {
            phrase_terms.push_back(term_node);
            // Erase the token index from the in_query_tokens vector, as the phrase will get one posting list after processing
            in_query_tokens.erase(in_query_tokens.begin() + index);
        }
        else if (curr_token->type == QueryProcessor::PHRASE_END)
        {
            // Process phrase query and append its posting list to the postings vector as a single entry
            phrase_terms.push_back(term_node);
            std::vector<int> phrase_postings = process_phrase(phrase_terms);

            if (phrase_postings.size())
            {
                postings.push_back(phrase_postings);
                ++index;
            }
            else
            {
                std::cout << "Phrase query excluded from the search because was not found in any document of the Inverted Index...\n";
                in_query_tokens.erase(in_query_tokens.begin() + index);
            }
        }
        else
        {
            // Add posting list for that term
            postings.push_back(term_node->info.positions);
            ++index;
        }
    }

    return postings;
}

// Function will get the positions for each term inside the documents where they are in, and then will check if there's a match for that particular phrase query
std::vector<int> InvertedIndex::process_phrase(const std::vector<const TermNode*> in_phrase_terms)
{
    // Initialize possible_doc_ids with the postings list of the first term
    std::vector<int> possible_doc_ids = in_phrase_terms[0]->info.positions;

    // Perform merge AND to find documents containing all terms
    for (size_t i = 1; i < in_phrase_terms.size() && !possible_doc_ids.empty(); ++i)
    {
        if (!in_phrase_terms[i]) continue; // Ignore invalid term

        possible_doc_ids = processor_.merge_and(possible_doc_ids, in_phrase_terms[i]->info.positions);
    }

    // To store documents where the phrase is found
    std::vector<int> matching_doc_ids;

    // Check each candidate document for the phrase
    for (int doc_id : possible_doc_ids)
    {
        // Check if the phrase appears in the document
        if (phrase_in_document(doc_id, in_phrase_terms))
        {
            matching_doc_ids.push_back(doc_id);
        }
    }

    return matching_doc_ids;
}

bool InvertedIndex::phrase_in_document(int doc_id, const std::vector<const TermNode*>& in_phrase_terms)
{
    // Get the positions of the first term
    const std::vector<int>* first_term_positions = positions_in_document(in_phrase_terms[0], doc_id);

    // Iterate over each starting position of the first term
    for (int start_pos : *first_term_positions)
    {
        bool match = true;

        // Check subsequent terms using two pointers
        for (size_t i = 1; i < in_phrase_terms.size(); ++i)
        {
            // Jump position of invalid terms in phrase queries (like stop-words)
            if (!in_phrase_terms[i]) continue;

            const std::vector<int>* next_term_positions = positions_in_document(in_phrase_terms[i], doc_id);

            // Use lower_bound to find the smallest position >= expected position
            int expected_pos = start_pos + static_cast<int>(i);
            auto it = std::lower_bound(next_term_positions->begin(), next_term_positions->end(), expected_pos);

            // If no position matches, or the closest position is not the expected one, break
            if (it == next_term_positions->end() || *it != expected_pos)
            {
                match = false;
                break;
            }
        }

        if (match)
            return true; // Phrase found
    }

    return false; // Phrase not found
}


const std::vector<int>* InvertedIndex::positions_in_document(const TermNode* in_term, int in_doc_id)
{
    const TermNode *doc_term_node = documents_[in_doc_id]->get_terms().find(in_term->word);

    return doc_term_node ? &doc_term_node->info.positions : nullptr;
}