/* TODO:
1. Write a function named NonEmpty that has one parameter, a vector of strings V,
and that returns another vector of strings that contains just the non-empty strings in V.
For example, if parameter V contains the 6 strings:
"hello", "", "bye, "", "", "!"
then function NonEmpty should create and return a vector that contains the 3 strings:
"hello", "bye, "!"

2. Write a function named Expand that has one parameter, a vector of ints V.
Expand should change V so that it is double its original size, and contains the values that were originally in V.
*/

#include <iostream>
#include <string>
#include <vector>

// Prototypes
std::vector<std::string> NonEmpty(const std::vector<std::string> &V);
void Expand(std::vector<int> &V);

// PROVIDED: Test your function with the following main function:
int main()
{
    std::string content_sep = "- - - - - - - - - - - - - - - - - - - - - - - - -\n";
    // 1) NonEmpty function
    std::vector<std::string> empty = {"hello", "", "bye", "", "", "!"};
    std::vector<std::string> non_empty = NonEmpty(empty);

    std::cout << "NonEmpty function test:\n" << content_sep
              << "Vector containig 6 strings (but 3 are empty). Size: " << empty.size()
              << "\nVector returned by the NonEmpty function. Size: " << non_empty.size() << std::endl
              << content_sep;

    // 2) Expand function
    std::cout << "\nExpand function test\n" << content_sep;
    std::vector<int> v(1);

    for (int k = 0; k < 16; k++)
    {
        if (v.size() <= k)
        {
            std::cout << "vector size before calling Expand: " << v.size() << std::endl;
            Expand(v);
            std::cout << "vector size after calling Expand: " << v.size() << std::endl;
        }
        v[k] = k + 1;
    }

    std::cout << "[ ";
    for (int k = 0; k < v.size(); k++)
    {
        std::cout << v[k] << ' ';
    }
    std::cout << "]\n" << content_sep;

    return 0;
}

std::vector<std::string> NonEmpty(const std::vector<std::string> &V)
{
    // Create a vector of strings
    std::vector<std::string> non_empty;

    // Loop through the strings in V and assign them to the new vector (if not empty)
    for (int i = 0; i < V.size(); ++i)
        if (!(V[i].empty()))
            non_empty.push_back(V[i]);

    return non_empty;
}

void Expand(std::vector<int> &V)
{
    V.resize(V.size() * 2);
}