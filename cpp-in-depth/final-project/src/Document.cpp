#include "../include/Document.h"

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