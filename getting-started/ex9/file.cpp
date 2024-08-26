/* TODO: 
Figure out how to open the file just created (by example in `file-ex.cpp`), and display the data. */

#include <fstream>  // std::ifstream
#include <iostream>

int main(int argc, char *argv[])
{
    // Check for command-line arguments
    if (argc != 2)
    {
        std::cout << "Usage: file.cpp your_file.txt\n";
        return 1;
    }

    // Construct an ifstream object with file provided in argv[1]
    std::ifstream File(argv[1], std::ifstream::in);

    // Checks if could open file
    if (!File)
    {
        std::cout << "Could not open file: " << argv[1] << std::endl;
        return 1;
    }

    // Display the contents of File
    char line[256];
    while (File.getline(line, sizeof(line)))
        std::cout << line << std::endl;
    
    File.close();
    return 0;
}
