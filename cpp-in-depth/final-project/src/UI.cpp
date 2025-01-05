#include "../include/UI.h"

// MENU
void UI::display_menu(const std::string &title)
{
    std::cout << '\n' << menu_sep_line() << '\n' << title << '\n' << submenu_sep_line() << "\n\n";
}

void UI::press_enter()
{
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << '\n';
}

void UI::end_menu()
{
    std::cout << menu_sep_line() << "\n\n";
    press_enter();
}

// CONTENT
void UI::display_content(const std::string &message)
{
    std::cout << '\n' << content_sep_line() << '\n' << message << '\n' << content_sep_line() << "\n\n";
}

void UI::display_path_of_documents(const std::vector<Document*>& in_documents)
{
    std::string buffer = "Paths for the " + std::to_string(in_documents.size()) + " documents in the Inverted Index";
    UI::display_menu(buffer);

    std::cout << UI::content_sep_line() << '\n';
    for (Document *doc_ptr : in_documents)
    {
        std::cout << doc_ptr->get_path() << std::endl;
    }
    std::cout << UI::content_sep_line() << "\n\n";

    UI::end_menu();
}

void UI::display_location_data(const std::vector<Document*> in_documents, const std::vector<int>& in_doc_ids)
{
    std::cout << UI::content_sep_line() << '\n';
    
    const Document *curr_document = nullptr;

    for (int doc_id : in_doc_ids)
    {
        curr_document = in_documents[doc_id];
        std::cout << "DocID: " << curr_document->get_doc_id() << " - Path: " << curr_document->get_path() << std::endl;
    }
    std::cout << UI::content_sep_line() << "\n\n";

    UI::end_menu();
}

void UI::display_sequence_in_document(const Document* in_doc, int position_begin, int position_end, int context_words)
{
    std::stringstream text_stream(in_doc->get_text());
    std::string word;
    std::vector<std::string> words;

    // Extract all words into a vector for easier manipulation
    while (text_stream >> word)
    {
        words.push_back(word);
    }

    int total_words = words.size();
    position_begin = std::max(0, position_begin - context_words); // Add context before the match
    position_end = std::min(total_words, position_end + context_words); // Add context after the match

    std::cout << '\n' << UI::submenu_sep_line() << "\nPhrase query matched in \"" << in_doc->get_path() << "\" - DocID: " << in_doc->get_doc_id() << " - Positions: " << position_begin << " to " << position_end <<  "\n";
    std::cout << UI::subcontent_sep_line() << "\n\"... ";

    for (int i = position_begin; i < position_end; ++i)
    {
        std::cout << words[i] << ' ';
    }
    std::cout << "...\"\n" << UI::subcontent_sep_line() << "\n" << UI::submenu_sep_line();
}