#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class Document
{
    std::string text_;
    std::vector<std::string> words_;

public:
    // Constructor
    Document(const std::string &file_path);

    // Methods
private:
    void load_from_file(const std::string &file_path);
    void tokenize();

public:
    // Accessors
    const std::string &get_text() const { return text_; }
    const std::vector<std::string> &get_words() const { return words_; }
};