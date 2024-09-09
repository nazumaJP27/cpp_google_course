/* Database Project: Composer DB.
In this project, we create a fully functional C++ program that implements a simple database application.
The program will allow us to manage a database of composers and relevant information about them.
The features of the program include:
    - The ability to add a new composer
    - The ability to rank a composer (i.e., indicate how much we like or dislike the composer's music)
    - The ability to view all the composers in the database
    - The ability to view all composers by rank
Example run:
---------------------------------------------
Composer Database
******************************************
1) Add a new composer
2) Retrieve a composer's data
3) Promote/demote a composer's rank
4) List all composers
5) List all composers by rank
0) Quit
---------------------------------------------
TODO:
Write a program that implements the user interface for this database with all these features. */

#include "../include/Database.h"

#include <limits>   // std::numeric_limits
#include <string>
#include <iostream>

struct UserInterface
{
    Database *db_;
    bool running_;
    // Constructor
    UserInterface(Database *DB) : db_(DB), running_(true) {}
    // Methods
    int menu();
    void add_composer();
    void composer_info();
    void promote_demote();
    void list_all();
    void list_by_rank();
    void quit();

private:
    void menus_sep_line() { std::cout << "***************************************************\n"; }
    void submenus_sep_line() { std::cout << "--------------------------------------------------\n"; }
    void content_sep_line() { std::cout << "- - - - - - - - - - - - - - - - -\n"; }
};

// Prototypes
int get_int(const std::string &prompt="Number: ", int max=10);
std::string get_string(const std::string &prompt="String: ");

int main()
{
    Database DB;
    UserInterface UI(&DB);

    // Buffer to hold the user's input used to navigate through the program
    unsigned int user_nav;

    while (UI.running_)
    {
        // Display the user interface menu and return a user input (0-5)
        user_nav = UI.menu();
        switch (user_nav)
        {
            case 0:
                UI.quit();
                break;
            case 1:
                UI.add_composer();
                break;
            case 2:
                UI.composer_info();
                break;
            case 3:
                UI.promote_demote();
                break;
            case 4:
                UI.list_all();
                break;
            case 5:
                UI.list_by_rank();
                break;
            // Should not get to default
            default:
                std::cout << "Something unexpected happened.\n";
                break;
        }
    };

    std::cout << "All done...\n";
    return 0;
}

int UserInterface::menu()
{
    // Display menu
    menus_sep_line();
    std::cout << "Composer Database\n";
    submenus_sep_line();
    std::cout << "1) Add a new composer\n2) Retrieve a composer's data\n"
              << "3) Promote/Demote a composer's rank\n4) List all composers\n"
              << "5) List all composers by rank\n0) Quit\n";

    // Gets an integer from the user
    int input = get_int("", 5);

    menus_sep_line();
    return input;
}

void UserInterface::add_composer()
{
    menus_sep_line();
    std::cout << "Add a new composer\n";
    submenus_sep_line();
    
    // Get composer data from the user
    std::string in_first_name = get_string("First name: ");
    std::string in_last_name = get_string("Last name: ");
    int in_birth = get_int("Year of birth: ", 2024);
    std::string in_genre = get_string("Genre: ");
    std::string in_fact = get_string("Fact: ");

    // Add Composer object into Database object
    db_->add_composer(in_first_name, in_last_name, in_birth, in_genre, in_fact);

    menus_sep_line();
    return;
}

void UserInterface::composer_info()
{
    menus_sep_line();
    std::cout << "Retrieve a composer's data\n";
    submenus_sep_line();
    
    // Prompt for the composer's last name
    std::string in_last_name;
    std::cout << "Search for a composer by typing the last name (case insensitive).\n";
    Composer *composer;
    do
    {
        in_last_name = get_string("Last name: ");
        composer = db_->get_composer(in_last_name);
        std::cout << '\n';
        content_sep_line();

        if (!composer)
        {
            std::cout << "Composer not found in the database...\n";
            content_sep_line();
            // Wait for the user to press Enter/Return key
            std::cout << "Press Enter to continue... ";
            std::cin.get();
        }
        else
        {
            composer->display();
            content_sep_line();
            // Wait for the user to press Enter/Return key
            std::cout << "Press Enter to continue... ";
            std::cin.get();
        }
    } while (in_last_name.empty());

    menus_sep_line();
    return;
}

void UserInterface::promote_demote()
{
    menus_sep_line();
    std::cout << "Promote/demote a composer's rank\n";
    submenus_sep_line();
    
    // Prompt for the composer's last name
    std::string in_last_name;
    std::cout << "Search for a composer by typing the last name (case insensitive).\n";
    Composer *composer;
    do
    {
        in_last_name = get_string("Last name: ");
        composer = db_->get_composer(in_last_name);
        std::cout << '\n';
        content_sep_line();

        if (!composer)
        {
            std::cout << "Composer not found in the database...\n";
            content_sep_line();
            // Wait for the user to press Enter/Return key
            std::cout << "Press Enter to continue... ";
            std::cin.get();
        }
        else
        {
            composer->display();
            std::cout << "Ranking: " << composer->get_ranking() << std::endl;
            content_sep_line();

            // Prompt for demote or promote the composer
            int input = get_int("Promote (1) / Demote (0): ", 1);

            int promote_demote;
            if (input == 0)
            {
                promote_demote = get_int("Demote: ", 10);
                composer->demote(promote_demote);
            }
            else
            {
                promote_demote = get_int("Promote: ", 10);
                composer->promote(promote_demote);
            }

            // Wait for the user to press Enter/Return key
            std::cout << "Press Enter to continue... ";
            std::cin.get();
        }
    } while (in_last_name.empty());

    menus_sep_line();
    return;
}

void UserInterface::list_all()
{
    menus_sep_line();
    std::cout << "List all composers\n";
    submenus_sep_line();
    db_->display_all();
    // Wait for the user to press Enter/Return key
        std::cout << "Press Enter to continue... ";
        std::cin.get();

    menus_sep_line();
    return;
}

void UserInterface::list_by_rank()
{
    menus_sep_line();
    std::cout << "List all composers by rank\n";
    submenus_sep_line();
    db_->display_by_rank();

    // Wait for the user to press Enter/Return key
        std::cout << "Press Enter to continue... ";
        std::cin.get();
    menus_sep_line();
    return;
}

void UserInterface::quit()
{
    running_ = false;
    return;
}

// Prompt [custom prompt], validate [range 0 through max], and return an int
int get_int(const std::string &prompt, int max)
{
    int input;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> input))
        {
            std::cin.clear();
            std::cout << "Input error. Enter an integer number from 0 to " << max << ".\n";
            input = -1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    while (input < 0 || input > max);
    return input;
}

std::string get_string(const std::string &prompt)
{
    std::string input;
    do
    {
        std::cout << prompt;
        std::getline(std::cin, input);
        if (input.empty())
        {
            std::cout << "Input cannot be empty. Please try again.\n";
        }
    }
    while (input.empty());
    
    return input;
}