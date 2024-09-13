// IntList class test

#include "IntList.h"
#include <iostream>

int main()
{
    IntList list;

    list.add_to_end(1);
    list.add_to_end(2);
    list.add_to_end(3);
    list.add_to_end(4);
    list.add_to_end(5);

    list.print_list();

    std::cout << list.get_length() << std::endl;

    list.~IntList();

    list = IntList(3, 3);

    list.print_list();
}