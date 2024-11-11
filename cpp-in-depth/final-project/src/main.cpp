#include "../include/utils.h"
#include "../include/Document.h"
#include "../include/InvertedIndex.h"

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

    InvertedIndex ii(docs_path);
    std::vector<Document*> documents = ii.get_documents();

    std::cout << "Paths for the " << documents.size() << " documents in the Inverted Index:\n";
    for (Document *doc_ptr : documents)
    {
        std::cout << doc_ptr->get_path() << std::endl;
    }

    std::string input_query;

    std::cout << "\nQuery to search the Inverted Index: ";
    std::getline(std::cin, input_query);
    std::vector<int> doc_ids_for_query = ii.process_query(input_query);
    int num_docs = doc_ids_for_query.size();

    if (num_docs > 0)
    {
        std::cout << "\nReturned " << num_docs << " out of " << documents.size() << " total documents after processing the query \"" << input_query << "\":\n";
        const Document *curr_document = nullptr;
        for (int doc_id : doc_ids_for_query)
        {
            curr_document = documents[doc_id];
            std::cout << "DocID: " << curr_document->get_doc_id() << " - Path: " << curr_document->get_path() << std::endl;
        }
    }
    return 0;
}