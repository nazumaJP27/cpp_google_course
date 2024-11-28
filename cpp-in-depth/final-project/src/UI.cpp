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