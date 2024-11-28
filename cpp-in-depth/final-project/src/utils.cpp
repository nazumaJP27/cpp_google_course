#include "../include/utils.h"
#include "../include/QueryProcessor.h" // QueryProcessor::is_stop_word
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
    if (in_word.length() > TERM_MAX_LENGTH || in_word.empty() || QueryProcessor::is_stop_word(in_word))
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
    std::string word = QueryProcessor::normalize(in_word);
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
    std::cout << "Search query: ";

    std::getline(std::cin, input_query_buffer);
}