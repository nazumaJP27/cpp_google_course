#include "../include/ATM.h"

// Constructor
ATM::ATM(int id, const std::string place, const std::string bank_name, const std::string bank_address)
    : state_(OFF), id_(id), place_(place), bank_name(bank_name), bank_address_(bank_address), card_inserted_(false), initial_cash_(0), 
      p_card_(nullptr), operator_panel_(this), card_reader_(this), cash_dispenser_(), bank_DB_(bank_address_) {}

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
    std::cout << "ATM shutdown...\n"
              << "The operator is now free to remove deposited envelopes, replenish cash and paper, etc...\n";
    // Reset cash variables
    initial_cash_.spend_all();
    cash_dispenser_ = CashDispenser();
}

void ATM::run()
{
    // The customer inserted a card into the atm [TEST]
    if (card_reader_.read_card(p_card_))
    {
        card_inserted();
        // Get account to start the session
        if (!(session_.start_session(bank_DB_.get_account(card_reader_.get_card_number()))))
        {
            set_state(IDLE);
            return;
        }
        else
        {
            set_state(SERVING_CUSTOMER);
        }
    }
    else
    {
        std::cout << "CU";
        set_state(IDLE);
        return;
    }

    // Instanciate a money object (ZERO DOLLARS) to hold the transaction amount
    Money in_transaction_money(0);

    bool valid_transaction = false;
    while (state_ == SERVING_CUSTOMER)
    {
        switch (customer_console_.get_transaction())
        {
        case DEPOSIT:
            valid_transaction = handle_deposit(&in_transaction_money);
            break;
        case WITHDRAW:
            valid_transaction = handle_withdraw(&in_transaction_money);
            break;
        case TRANSFER:
            valid_transaction = handle_transfer(&in_transaction_money);
            break;
        default:
            break;
        }

        if (valid_transaction)
        {
            // Process transaction, update accounts in the bank database, and reset the Money transaction object
            session_.process_transaction();
            bank_DB_.update_DB(bank_address_);
            in_transaction_money.spend_all();
        }

        // WILL Ask if the user wants to make another transaction
        // Then will set state to IDLE [TEST]
        set_state(IDLE);
    }
}

bool ATM::handle_deposit(Money *transaction_money)
{
    // Prompt for transaction money amount
    transaction_money->set_money(customer_console_.get_money());

    if (session_.start_transaction(DEPOSIT, transaction_money))
        return true;
    else
        return false;
}

bool ATM::handle_withdraw(Money *transaction_money)
{
    // Prompt for transaction money amount
    transaction_money->set_money(customer_console_.get_money());

    // Check if cash dispenser has the amount of cash needed for the operation
    if (cash_dispenser_.check_cash_on_hand(transaction_money))
    {
        if (session_.start_transaction(WITHDRAW, transaction_money))
        {
            // Subtract the transaction amount from the cash dispenser
            cash_dispenser_.dispense_cash(transaction_money);
            return true;
        }
        else
            return false;
    }
    else
    {
        std::cout << "Insuficient cash in the ATM cash dispenser.\nMaximum value for withdraw operations: "
                  << cash_dispenser_.get_cash_on_hand()->to_string();
        return false;
    }
}

bool ATM::handle_transfer(Money *transaction_money)
{
    // Prompt for transaction money amount
    transaction_money->set_money(customer_console_.get_money());

    // Prompt for the target account for the TRANSFER operation
    Account *in_transfer_target = nullptr;
    std::string in_card_number;
    std::cout << "Enter the card number corresponding to the account to which you want to make the transfer.\n";
    do
    {
        in_card_number = customer_console_.get_card_number();
    }
    while (!(in_transfer_target = bank_DB_.get_account(in_card_number)));

    if (session_.start_transaction(TRANSFER, transaction_money, in_transfer_target))
        return true;
    else
        return false;
}