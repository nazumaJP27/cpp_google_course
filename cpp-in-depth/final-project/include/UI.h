#pragma once

#include "Document.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

class UI
{
public:
    // Methods
    static void display_menu(const std::string &title);
    static void display_content(const std::string &message);
    static void end_menu();

    static void press_enter();

    static std::string menu_sep_line() { return "***************************************************"; }
    static std::string submenu_sep_line() { return "---------------------------------------------------"; }
    static std::string content_sep_line() { return "- - - - - - - - - - - - - - - - - - - -"; }
    static std::string subcontent_sep_line() { return ". . . . . . . . . . . . . . . . . ."; }

    static void display_path_of_documents(const std::vector<Document*>& in_documents);
    static void display_location_data(const std::vector<Document*> in_documents, const std::vector<int>& in_doc_ids);
    static void display_sequence_in_document(const Document* in_doc, int postion_begin, int position_end);
};