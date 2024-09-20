#include "../include/ATM.h"

// Constructor
ATM::ATM(int id, const std::string place, const std::string bank_name)
    : state_(OFF), id_(id), place_(place), bank_name(bank_name), card_inserted_(false), initial_cash_(0), 
      operator_panel_(this), card_reader_(this) {}

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

void ATM::card_inserted()
{
    card_inserted_ = true;
}

void ATM::perform_startup()
{
    std::cout << "ATM turning on...\n"
              << "The operator now need to enter the current amount of money inside the ATM...\n";
    // Asks operator to enter the amount of money currently in the cash dispenser
    initial_cash_ = operator_panel_.get_initial_cash();
    cash_dispenser_.set_initial_cash(&initial_cash_);
}

void ATM::perform_shutdown()
{
    // The connection with the "bank" is closed
    // Close CSVs
    std::cout << "ATM shutdown...\n"
              << "The operator is now free to remove deposited envelopes, replenish cash and paper, etc...\n";
}
