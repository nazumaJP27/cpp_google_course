#include "../include/ATM.h"

// Constructor
ATM::ATM(int id, const std::string place, const std::string bank)
    : id_(id), place_(place), bank_(bank), state_(OFF), operator_panel_(this), card_reader_(this) {}

// Only used by the operator
void ATM::turn_on()
{
    if (state_ == OFF)
    {
        state_ = IDLE;
        perform_startup();
    }
}

void ATM::turn_off()
{
    if (state_ == IDLE)
    {
        state_ = OFF;
        perform_shutdown();
    }
}

void ATM::perform_startup()
{
    // Asks operator to enter the amount of money currently in the cash dispenser
    initial_cash_ = operator_panel_.get_initial_cash();
}

void ATM::perform_shutdown()
{
    // The connection with the "bank" is closed
    // Close CSVs
    std::cout << "The operator is now free to remove deposited envelopes, replenish cash and paper, etc...\n";

}
