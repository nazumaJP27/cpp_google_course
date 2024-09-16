#include "../include/ATM.h"

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
}

void ATM::perform_shutdown()
{
    // The connection with the "bank" is closed
}
