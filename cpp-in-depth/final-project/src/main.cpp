#include "../include/utils.h"
#include "../include/Document.h"
#include "../include/InvertedIndex.h"
#include "../include/QueryProcessor.h"
#include "../include/UI.h"

#include <iostream>

int main(int argc, char *argv[])
{
    std::string docs_path;

    if (argc == 2)
    {
        docs_path = argv[1];
    }
    else
    {
        docs_path = DEFAULT_DOCS_PATH;
    }

    // Iniatialize an InvertedIndex with the docs_path
    InvertedIndex ii(docs_path);
    std::vector<Document*> documents = ii.get_documents();

    // Display the path for the files used to instantiate each Document object
    UI::display_path_of_documents(documents);

    // Get a query from the user, process it, and display the location data
    std::string input_query;
    get_query(input_query);

    std::vector<int> doc_ids_for_query = ii.process_query(input_query);
    int num_docs = doc_ids_for_query.size();


    if (num_docs > 0)
    {
        std::cout << "\nReturned " << num_docs << " out of " << documents.size() << " total documents after processing the query \"" << input_query << "\":\n\n";
        UI::display_location_data(documents, doc_ids_for_query);
    }
    else
    {
        std::cout << "There's no match after processing the query \"" << input_query << "\"...\n";
    }

    return 0;
}