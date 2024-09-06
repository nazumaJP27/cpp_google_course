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


/* Future header files:
#include <database.h>
#include <user-interface.h> */

#include <iostream>

int main()
{
    Database DB;
    UserInterface UI(DB);

    // Buffer to hold the user's input used to navigate through the program
    unsigned int user_nav;

    do
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
                std::cout << "Something unexpected happened."
                break;
        }
    } while (UI.status != QUIT);

    return 0;
}