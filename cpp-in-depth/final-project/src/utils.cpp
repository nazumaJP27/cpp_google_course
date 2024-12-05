#include "../include/utils.h"
#include "../include/UI.h"

// HashTable ::
// Constructor 
HashTable::HashTable(unsigned int size) : table_(new TermNode*[size]), size_(size)
{
    for (unsigned int i = 0; i < size; ++i)
    {
        table_[i] = nullptr;
    }
}

// Destructor
HashTable::~HashTable()
{
    TermNode *curr = nullptr;
    TermNode *temp = nullptr;
    for (unsigned int i = 0; i < size_; ++i)
    {
        curr = table_[i];
        while (curr != nullptr)
        {
            temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
    delete [] table_;
}

const unsigned int HashTable::hash(const std::string &key) const
{
    return std::hash<std::string>{}(key) % size_;
}

void HashTable::insert(const std::string &in_word, const int &in_position) const
{
    if (in_word.length() > TERM_MAX_LENGTH || in_word.empty() || is_stop_word(in_word))
    {
        return;
    }

    unsigned int key = hash(in_word);

    if (table_[key] == nullptr)
    {
        table_[key] = new TermNode(in_word, in_position);
    }
    else
    {
        TermNode *cursor = table_[key];
        while(cursor->word != in_word && cursor->next != nullptr)
        {
            cursor = cursor->next;
        }
        if (cursor->word == in_word)
        {
            cursor->info.frequence++;
            cursor->info.positions.push_back(in_position);
        }
        else
        {
            cursor->next = new TermNode(in_word, in_position);
        }
    }
}

// Returns a nullpr if word not in hash table
TermNode* HashTable::find(const std::string &in_word) const
{
    std::string word = normalize(in_word);
    word = stem(word);
    unsigned int key = hash(word);
    TermNode *cursor = table_[key];

    if (cursor)
    {
        while (cursor->word != in_word)
        {
            cursor = cursor->next;
            if (!cursor)
            {
                // in_word not in table_
                break;
            }
        }
    }
    return cursor;
}

void get_query(std::string& input_query_buffer)
{
    std::string buffer = "Enter a query to search the Inverted Index";
    UI::display_menu(buffer);
    std::cout << "-> Search query: ";

    std::getline(std::cin, input_query_buffer);
}

bool is_stop_word(const std::string& in_word)
{
    return stop_words.find(in_word) != stop_words.end();
}

std::string normalize(const std::string& in_word)
{
    std::string out_word;
    for (char c : in_word)
    {
        if (std::isalpha(c))
        {
            out_word.push_back(std::tolower(c));
        }
    }
    return out_word;
}

// Simple implementation of a stemming function
std::string stem(const std::string& in_word)
{
    std::string stemmed_word = in_word;

    // Remove commom suffixes from words with more than 4 chars
    if (stemmed_word.size() > 4)
    {
        for (const std::string& suffix : suffixes)
        {
            if (is_suffix(stemmed_word, suffix))
            {
                remove_suffix(stemmed_word, suffix);
                break;
            }
        }
    }

    // Remove double consonant
    if (stemmed_word.size() > 2 && stemmed_word[stemmed_word.size() - 2] == stemmed_word[stemmed_word.size() - 1])
    {
        stemmed_word.erase(stemmed_word.end() - 1);
    }

    return stemmed_word;
}

bool is_suffix(const std::string& in_word, const std::string& in_suffix)
{
    return (in_word.size() >= in_suffix.size()) && in_word.substr(in_word.size() - in_suffix.size()) == in_suffix;
}

void remove_suffix(std::string& in_word, const std::string& in_suffix)
{
    if ((in_word.size() - in_suffix.size()) > 3 && is_suffix(in_word, in_suffix) )
        in_word.erase(in_word.size() - in_suffix.size());
}