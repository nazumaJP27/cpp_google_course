#pragma once

#include <iostream>
#include <string>

class Message
{
public:
    // Methods
    static void display_menu(const std::string &title);
    static void display_content(const std::string &message);

    static void end_menu() { std::cout << menu_sep_line(); }

    static std::string menu_sep_line() { return "\n***************************************************\n"; }
    static std::string submenu_sep_line() { return "\n---------------------------------------------------\n"; }
    static std::string content_sep_line() { return "\n- - - - - - - - - - - - - - - - - - - -\n"; }
};