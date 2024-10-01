#include "../include/Message.h"

// MENU
void Message::display_menu(const std::string &title)
{
    std::cout << menu_sep_line() << title << submenu_sep_line();
}

// CONTENT
void Message::display_content(const std::string &message)
{
    std::cout << content_sep_line() << message << content_sep_line();
}