/* TODO: 
Write a program similar to `file-ex.cpp`, but allow the user to enter many records of data using a loop.
Also read back all the data, one record at a time. */

#include <fstream>  // std::ifstream
#include <iostream>
#include <limits>   // std:numeric_limits

// Prototypes
void read_from_file(std::ifstream &file);
void write_to_file(std::ofstream& file);

int main()
{
    // Prompt for the name of the file to be created
    std::string file_name;
    std::cout << "Name of the new file (no spaces): "; std::cin >> file_name;

    // Append ".txt" to the file name
    file_name += ".txt";

    // Construct an ofstring object and open to write
    std::ofstream out_file(file_name, std::ios::out);
    if (!out_file)
    {
        std::cout << "Could not create new file: " << file_name << std::endl;
        return 1;
    }
    write_to_file(out_file);

    // Construct an ifstream object and display its contents
    std::ifstream in_file(file_name, std::ifstream::in);
    // Checks if could open file
    if (!in_file)
    {
        std::cout << "Could not open file: " << file_name << std::endl;
        return 1;
    }
    std::cout << "\nContent in " << file_name << ":" << std::endl;
    read_from_file(in_file);

    std::cout << "\nAll done.\n";
}

void write_to_file(std::ofstream &file)
{
    std::string input;
    int empty_line_count = 0, last_pos;

    // Write to out_file in a loop
    std::cout << "Write to file (enter two empty lines to close it):" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Reset input buffer

    while (empty_line_count < 2)
    {
        // If std::getline flag an error, shut down the program
        if (!(std::getline(std::cin, input)))
        {
            std::cout << "Input Error. Exitting the program...\n";
            return;
        }

        if (input.empty())
        {
            empty_line_count++;
            if (empty_line_count == 1)
            {
                std::cout << "(one more empty line will close the file)" << std::endl;
                file << input;
            }
        }
        else
        {
            empty_line_count = 0; // Reset count if a non-empty line is entered
            file << input << '\n';
        }
    }
    std::cout << "Closing and saving file..." << std::endl;
    file.close();
}

void read_from_file(std::ifstream &file)
{
    // Display the contents of File
    int line_number = 1;
    char line[256];
    while (file.getline(line, sizeof(line)))
    {
        std::cout << line_number << ":  " << line << std::endl;
        line_number++;
    }

    std::cout << "(end of file)" << std::endl;
    file.close();
}
