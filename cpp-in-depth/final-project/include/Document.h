#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <vector>

class Document
{
    struct Node
    {
        std::string data;
        Node *next;
    };

    struct WordInfo
    {
        int frequence = 0;
        std::vector<int> positions;
    };

    std::string text_;
    std::vector<std::string> words__;
    std::unordered_map<std::string, WordInfo> words_;

public:
    // Constructor
    Document(const std::string &file_path);

    // Private methods
private:
    void load_from_file(const std::string &file_path);
    void tokenize();

public:
    // Accessors
    const std::string &get_text() const { return text_; }
    const std::vector<std::string> &get_words() const { return words__; }
};