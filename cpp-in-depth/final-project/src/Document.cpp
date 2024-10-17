#include "../include/Document.h"
#include "../include/utils.h"

// Constructor
Document::Document(const std::string &file_path)
{
    load_from_file(file_path);
    tokenize();
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
    
    while (text_stream >> word)
    {
        word = normalize(word);
        words_.push_back(word);
    }
}