#pragma once

#include "utils.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

extern const char *DEFAULT_DOCS_PATH;
extern unsigned int DOC_ID;

class Document
{
    unsigned int doc_id_;
    std::string text_;
    HashTable terms_;
    std::string path_;

public:
    // Constructor
    Document(const std::string &file_path);

    // Private methods
private:
    void load_from_file(const std::string &file_path);
    void tokenize();

public:
    // Accessors
    const unsigned int get_doc_id() const { return doc_id_; }
    const std::string &get_text() const { return text_; }
    const HashTable &get_terms() const { return terms_; }
    const std::string &get_path() const { return path_; }
};