/* One of the powers of computing is being able to do a brute-force search for a solution to a problem.
Trial and error works just fine for some problems.
In fact, computers can be especially good at such problems.

How many ways can you arrange 6 different books, left to right, on a shelf?
This time we will just give you the solution and let you write the program: 720. */

#include <iostream>

// Prototypes
void initialize_shelf();

struct Shelf
{
    bool has_book;
};

const unsigned int N = 6;
Shelf shelf[N];

int main()
{
    initialize_shelf();

    int arranges = 0;

    for (int b0 = 0; b0 < N; b0++)
    {
        if (!shelf[b0].has_book) 
        {
            shelf[b0].has_book = true;
            for (int b1 = 0; b1 < N; b1++)
            {
                if (!shelf[b1].has_book)
                {
                    shelf[b1].has_book = true;
                    for (int b2 = 0; b2 < N; b2++)
                    {
                        if (!shelf[b2].has_book)
                        {
                            shelf[b2].has_book = true;
                            for (int b3 = 0; b3 < N; b3++)
                            {
                                if (!shelf[b3].has_book)
                                {
                                    shelf[b3].has_book = true;
                                    for (int b4 = 0; b4 < N; b4++)
                                    {
                                        if (!shelf[b4].has_book)
                                        {
                                            shelf[b4].has_book = true;
                                            for (int b5 = 0; b5 < N; b5++)
                                            {
                                                if (!shelf[b5].has_book)
                                                {
                                                    shelf[b5].has_book = true;
                                                    arranges++;
                                                    shelf[b5].has_book = false;
                                                }
                                            }
                                            shelf[b4].has_book = false;
                                        }
                                    }
                                    shelf[b3].has_book = false;
                                }
                            }
                            shelf[b2].has_book = false;
                        }
                    }
                    shelf[b1].has_book = false;
                }
            }
            shelf[b0].has_book = false;
        }
    }
    
    std::cout << "The number of possible arrangements for a shelf with six books is " << arranges << ".\n";
    return 0;
}

// Initialize every position in the shell to false
void initialize_shelf()
{
    for (int i = 0; i < N; i++)
    {
        shelf[i].has_book = false;
    }
}