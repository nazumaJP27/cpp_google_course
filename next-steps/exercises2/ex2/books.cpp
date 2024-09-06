/* Exercise 2: Book store.
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
 1 for reqd / 0 for optional: 1
 1 for used / 0 for new: 1
******************************************
Book: 1221
Price: $69.95
Inventory: 30
Enrollment: 150

This book is required and used.
******************************************
Need to order: 67
Total cost: $4686.65
******************************************

Enter 1 to add another book, 0 to stop. 0
******************************************
Total for all orders: $4686.65
Profit: $937.33
******************************************
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
#include <limits>
#include <vector>

const unsigned int STORE_PROFIT = 20; // Percentage of profit by each book purchase for the book store

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
    std::vector<Book> books_;
    float total_;
    float profit_;

    // Contructor
    Store() : total_(0.0), profit_(0.0) {}

    // Methods
    void add_book(Book book_obj);
    void display_total();
};

// Prototypes
bool add_book_sentinel(const std::string &prompt="Add another book? ");
Book get_Book();
int get_id_(const std::string &prompt="Id: ");
float get_price_(const std::string &prompt="Price: ");
int get_inventory_(const std::string &prompt="Inventory: ");
int get_enrollment_(const std::string &prompt="Enrollment: ");
bool get_required_(const std::string &prompt="Required (1) / Optional (0): ");
bool get_used_(const std::string &prompt="Used (1) / New (0): ");

int main()
{
    Store store;

    // Prompt the user to add books to the store in a loop
    do
    {
        // Create an instance of a Book
        Book book = get_Book();

        // Display object information
        std::cout << "******************************************\n";
        book.display_book();
        std::cout << "******************************************\n";
        book.display_order();
        std::cout << "******************************************\n";

        // Add to book to the store
        store.add_book(book);
    } while (add_book_sentinel("\nEnter 1 to add another book, 0 to stop. "));

    // Print the total cost of all the store orders and its profit
    std::cout << "******************************************\n";
    store.display_total();
    std::cout << "******************************************\n";

    return 0;
}

Book get_Book()
{
    // Prompt the user to enter all the needed values to construct a Book object
    int id = get_id_("Please enter the book code: ");
    float price = get_price_(" single copy price: ");
    int inventory = get_inventory_(" number on hand: ");
    int enrollment = get_enrollment_(" prospective enrollment: ");
    bool required = get_required_(" 1 for reqd / 0 for optional: ");
    bool used = get_used_(" 1 for used / 0 for new: ");

    // Return a Book object initialized with the values returned from each input function
    return Book(id, price, inventory, enrollment, required, used);
}

int get_id_(const std::string &prompt)
{
    int in_id = 0;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> in_id))
        {
            std::cin.clear();
            std::cout << "Invalid input. The book id can only contain integers." << std::endl;
            in_id = 0;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (in_id <= 0);

    return in_id;
}

float get_price_(const std::string &prompt)
{
    float in_price = 0;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> in_price))
        {
            std::cin.clear();
            std::cout << "Invalid input. The price must be in numeric digits." << std::endl;
            in_price = -0.1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (in_price < 0);

    return in_price;
}

int get_inventory_(const std::string &prompt)
{
    int in_inventory = 0;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> in_inventory))
        {
            std::cin.clear();
            std::cout << "Invalid input. The stock number must be an integer more than or equal to zero." << std::endl;
            in_inventory = -1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (in_inventory < 0);

    return in_inventory;
}

int get_enrollment_(const std::string &prompt)
{
    int in_enrollment = 0;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> in_enrollment))
        {
            std::cin.clear();
            std::cout << "Invalid input. The enrollment prospect must be an integer more than or equal to zero." << std::endl;
            in_enrollment = -1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (in_enrollment < 0);

    return in_enrollment;
}

bool get_required_(const std::string &prompt)
{
    int in_required = -1;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> in_required))
        {
            std::cin.clear();
            std::cout << "Invalid input. Enter 1 for required or 0 for optional." << std::endl;
            in_required = -1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (in_required != 0 && in_required != 1);

    return in_required;
}

bool get_used_(const std::string &prompt)
{
    int in_used = -1;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> in_used))
        {
            std::cin.clear();
            std::cout << "Invalid input. Enter 1 for used or 0 for new." << std::endl;
            in_used = -1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (in_used != 0 && in_used != 1);

    return in_used;
}

bool add_book_sentinel(const std::string &prompt)
{
    int sentinel = -1;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> sentinel))
        {
            std::cin.clear();
            std::cout << "Invalid input. Enter 1 to add another book or 0 to end." << std::endl;
            sentinel = -1;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (sentinel != 0 && sentinel != 1);

    return sentinel;
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

void Store::add_book(Book book_obj)
{
    // Add to book to books_
    books_.push_back(book_obj);
    total_ += book_obj.get_order_cost();
    profit_ = total_ * (STORE_PROFIT / 100.0);
}

void Store::display_total()
{
    std::cout.precision(2);
    std::cout << std::fixed
              << "Total for all orders: $" << total_
              << "\nProfit: $" << profit_ << std::endl;

    // Reset precision to default and unset fixed notation
    std::cout.unsetf(std::ios_base::fixed);
    std::cout.precision();
}