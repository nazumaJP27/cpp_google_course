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
    // Tokenize the query and parse for operators (AND, OR, NOT) for each term
    std::vector<QueryProcessor::QueryToken> query_tokens = processor_.parse_query(in_query);

    int len_query_tokens = query_tokens.size();

    if (len_query_tokens < 1)
    {
        // No terms found in the query
        std::cout << "No valid terms in the query...\n";
        return {};
    }

    // Get the TermNode* for the first term in the QueryToken vector
    int query_index = 0;
    const TermNode* first_term = ii_terms_.find(query_tokens[0].term);

    // If the term was not in the ii_terms_, attempt to start from the next term in the query (this ignores the operator for that particular term)
    while (!first_term)
    {
        std::cout << "Term \"" << query_tokens[query_index++].term << "\" excluded from the search because was not found in the Inverted Index...\n";
        if (query_index < len_query_tokens)
        {
            first_term = ii_terms_.find(query_tokens[query_index].term);
        }
        else
        {
            // There's no more valid terms in the query, return
            std::cout << "No valid terms in query...\n";
            return {};
        }
    }

    // Initialize possible_doc_ids with the postings list of the first term
    std::vector<int> possible_doc_ids = first_term->info.positions;

    // Merge each subsequent term's posting list with possible_doc_ids and apply operators
    while (possible_doc_ids.size() && ++query_index < len_query_tokens)
    {
        const QueryProcessor::QueryToken& token = query_tokens[query_index];
        const TermNode* term_node = ii_terms_.find(token.term);

        if (!term_node)
        {
            std::cout << "Term \"" << token.term << "\" excluded from the search because was not found in the Inverted Index...\n";
            continue;
        }

        // Get postings for the current term
        const std::vector<int> &postings = term_node->info.positions;

        // Apply the corresponding merge operator
        switch (token.op)
        {
            case QueryProcessor::OR:
                possible_doc_ids = processor_.merge_or(possible_doc_ids, postings);
                break;
            case QueryProcessor::NOT:
                possible_doc_ids = processor_.merge_not(possible_doc_ids, postings);
                break;
            case QueryProcessor::AND:
            case QueryProcessor::NONE:
                possible_doc_ids = processor_.merge_and(possible_doc_ids, postings);
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
        if (word == "AND" || word == "OR" || word == "NOT")
        word = QueryProcessor::normalize(word);
        if (word.length() > TERM_MAX_LENGTH || word.empty() || QueryProcessor::is_stop_word(word))
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