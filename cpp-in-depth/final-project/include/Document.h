#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

class Document
{
    std::string text_;
    std::vector<std::string> words;

public:
    // Methods
    void load_from_file(const std::string &file_path);

    // Accessors
    const std::string &get_text() const { return text_; }
};