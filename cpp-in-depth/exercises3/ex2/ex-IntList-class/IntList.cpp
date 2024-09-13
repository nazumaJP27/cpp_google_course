#include "IntList.h"

// Default constructor
IntList::IntList() : items_(new int[SIZE]), num_items_(0), array_size_(SIZE) {}

// Constructor that initialize the array with n copies of value 
IntList::IntList(int n, int value) : IntList()
{
    for (int i = 0; i < n; ++i)
        add_to_end(value);
}

// Destructor
IntList::~IntList() { delete[] items_; }

// num_items_ accessor
int IntList::get_length() const { return num_items_; }

// Add i to the end of the array
void IntList::add_to_end(int i)
{
    // Check if the array is full
    if (num_items_ >= array_size_)
        resize();

    // Assign i to the first empty index of items_ and then increment num_items_
    items_[num_items_++] = i;
}

// Allocate memory for an array double the size of current array items_ is pointing
void IntList::resize()
{
    // Allocate memory for another array with twice the previous size
    array_size_ *= 2;
    int *tmp = new int[array_size_];

    // Copy the contents inside the items_ array into the new one
    std::copy(items_, items_ + num_items_, tmp);

    // Deallocate the memory in items_
    delete[] items_;
    items_ = tmp;
}

void IntList::print_list() const
{   
    std::cout << "[";
    for (int i = 0; i < num_items_; ++i)
    {
        i > 0 ? std::cout << ", " : std::cout << "";
        std::cout << items_[i];
    }
    std::cout << ']' << std::endl;
}