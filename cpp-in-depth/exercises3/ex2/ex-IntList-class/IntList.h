#pragma once

#include <algorithm> // std::copy
#include <iostream>

class IntList 
{
    static const int SIZE = 10; // Initial size of the array
    int *items_;                // Pointer to the dynamically allocated array
    int num_items_;             // Number of items inside the array
    int array_size_;            // Current size of the array

public:
    // Constructors
    IntList();
    IntList(int n, int value);

    // Destructor
    ~IntList();

    // Methods
    void add_to_end(int i);  // Add i to the end of the array
    void print_list() const; // Print the list

    // Accessor
    int get_length() const;

private:
    void resize(); // Allocate memory for a array double the size of items_
};