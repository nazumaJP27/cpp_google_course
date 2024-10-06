#include "../include/ATM.h"
#include <cstring>

int main(int argc, char *argv[])
{
    ATM *atm;

    // Check for custom settings
    if (argc == 2 && std::strcmp(argv[1], "-h") == 0)
    {
        std::cout << "Usage: ./ATM [OPTIONS]\n\n"
                  << "Options:\n"
                  << "  (no arguments)          Use default bank settings (accounts.csv)\n"
                  << "  <atm_id> <bank_place> <bank_name> <bank_file>  Use custom bank settings\n\n"
                  << "Examples:\n"
                  << "  ./ATM-test                   Run with default sample bank\n"
                  << "  ./ATM-test 001 NewYork CitiBank bank_data.csv  Run with custom settings\n";
        return 0;
    }
    else if (argc == 5)
    {
        // Custom bank settings
        atm = new ATM(std::stoi(argv[1]), argv[2], argv[3], argv[4]);
    }
    else
    {
        // Default bank settings
        atm = new ATM();
    }

    // Instanciate a CustumerConsole object to get a card number for the simulation
    CustomerConsole card_getter;

    // Create a test card
    Card card(card_getter.get_card_number(), "GENERICFLAG");

    atm->turn_on();
    atm->run(&card);

    delete atm;
    return 0;
}