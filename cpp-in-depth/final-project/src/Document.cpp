#include "../include/Document.h"

const char *DEFAULT_DOCS_PATH = "test-books";
unsigned int DOC_ID = 0; // Starts at 0 and is incremented by 1 on each Document object instantiation

// Constructor
Document::Document(const std::string &file_path=DEFAULT_DOCS_PATH) : doc_id(DOC_ID)
{
    load_from_file(file_path);
    tokenize();
    ++DOC_ID;
}

void Document::load_from_file(const std::string &file_path)
{
    std::ifstream file(file_path);
    if (!(file))
    {
        std::cerr << "Could not open file: " << file_path << '\n';
    }
    else
    {
        // Reads the entire file into the text_ member variable
        text_.append(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }
}

void Document::tokenize()
{
    std::stringstream text_stream(text_);
    std::string word;
    int word_position = 0;
    
    while (text_stream >> word)
    {
        word = normalize(word);
        terms_.insert(word, word_position);
        ++word_position;
    }
}