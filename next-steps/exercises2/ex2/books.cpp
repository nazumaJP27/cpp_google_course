/* Exercise 2: Book store. [work in progress]
Your college book store needs your help in estimating its business for next year.
Experience has shown that sales depend greatly on whether a book is required for a course or just optional,
and whether or not it has been used in the class before.
A new, required textbook will sell to 90% of prospective enrollment,
but if it has been used in the class before, only 65% will buy.
Similarly, 40% of prospective enrollment will buy a new, optional textbook,
but if it has been used in the class before only 20% will buy.
Example run:
---------------------------------------------
Please enter the book code: 1221
    single copy price: 69.95
    number on hand: 30
    prospective enrollment: 150
    1 for reqd/0 for optional: 1
    1 for new/0 for used: 0
***************************************************
Book: 1221
Price: $69.95
Inventory: 30
Enrollment: 150

This book is required and used.
***************************************************
Need to order: 67
Total Cost: $4686.65
***************************************************

Enter 1 to do another book, 0 to stop. 0
***************************************************
Total for all orders: $4686.65
Profit: $937.33
***************************************************
---------------------------------------------
TODO:
Write a program that accepts as input a series of books (until the user enters a sentinel).
For each book ask for: a code for the book, the single copy cost for the book,
the current number of books on hand, the prospective class enrollment,
and data that indicates if the book is required/optional, new/used in past.
As output, show all the input information in a nicely formatted screen along with how many books must be ordered,
and the total cost of each order.
Then, after all input is complete, show the total cost of all book orders,
and the expected profit if the store pays 80% of list price.
*/
#include <iostream>
#include <vector>

// Percentage of book sales
enum Sale_Percentage
{
    OPTL_USED = 20, // Optional and used book
    OPTL_NEW = 40,  // Optional and new book
    REQD_USED = 65, // Required and used book
    REQD_NEW = 90   // Required and new book
};

class Book
{
    int id_;
    float price_;
    int inventory_, enrollment_;
    bool required_, used_;
    float sale_percentage_;
    int num_to_buy_;
    float order_cost_;

public:
    // Constructor
    Book(int id, float price, int inventory, int enrollment, bool required, bool used) :
        id_(id), price_(price), inventory_(inventory), enrollment_(enrollment), required_(required), used_(used)
        {
            set_sale_percentage();
            set_num_to_buy();
            set_order_cost();
        }

    // Methods
    void display_book();
    void display_order();
    float get_sale_percentage() { return sale_percentage_; }
    float get_order_cost() { return order_cost_; }
    void set_num_to_buy();
    void set_order_cost();
    void set_sale_percentage();
};

struct Store
{
    std::vector<Book> books;

};

int main()
{
    Store store;
    Book book(1221, 69.95, 30, 150, true, true);

    std::cout << "******************************************\n";
    book.display_book();
    std::cout << "******************************************\n";
    book.display_order();
    std::cout << "******************************************\n";

    return 0;
}

// Print the book info to the console
void Book::display_book()
{
    std::cout << "Book: " << id_
              << "\nPrice: $" << price_
              << "\nInventory: " << inventory_
              << "\nEnrollment: " << enrollment_ << std::endl;

    // Set strings variables to print if the book is required/optionl and used/new
    std::string required_optional, used_new;
    if (required_)
        required_optional = "required";
    else
        required_optional = "optional";
    
    if (used_)
        used_new = "used";
    else
        used_new = "new";

    std::cout << "\nThis book is " << required_optional << " and " << used_new << ".\n";
}

// Check the member vars required_, and used_ to assign the corresponding sale percentage
void Book::set_sale_percentage()
{
    if (required_)
        sale_percentage_ = (used_ ? REQD_USED / 100.0 : REQD_NEW / 100.0);
    else
        sale_percentage_ = (used_ ? OPTL_USED / 100.0 : OPTL_NEW / 100.0);
}

void Book::set_num_to_buy()
{
    num_to_buy_ = enrollment_ * sale_percentage_ - inventory_;
    if (num_to_buy_ < 0)
        num_to_buy_ = 0;
}

void Book::set_order_cost()
{
    order_cost_ = num_to_buy_ * price_;
}

void Book::display_order()
{
    std::cout << "Need to order: " << num_to_buy_
              << "\nTotal cost: $" << order_cost_ << std::endl;
};