#include "../include/ATM.h"

// Constructor
ATM::ATM(int id, const std::string place, const std::string bank_name, const std::string bank_address)
    : state_(OFF), id_(id), place_(place), bank_name(bank_name), bank_address_(bank_address), initial_cash_(0), 
      operator_panel_(this), card_reader_(this), cash_dispenser_(), bank_DB_(bank_address_) {}

// Only used by the operator
void ATM::turn_on()
{
    if (state_ == OFF)
    {
        perform_startup();
        set_state(IDLE);
    }
}

void ATM::turn_off()
{
    if (state_ == IDLE)
    {
        perform_shutdown();
        set_state(OFF);
    }
}

void ATM::perform_startup()
{   
    Message::display_content("ATM turning on...\nThe operator now need to enter the current amount of money inside the ATM...");
    // Asks operator to enter the amount of money currently in the cash dispenser
    Message::display_menu("OPERATOR PANEL");
    initial_cash_ = operator_panel_.get_initial_cash();
    cash_dispenser_.set_initial_cash(&initial_cash_);
    Message::end_menu();
}

void ATM::perform_shutdown()
{
    Message::display_content("ATM shutdown...\nThe operator is now free to remove deposited envelopes, replenish cash and paper, etc...");
    // Reset cash variables
    initial_cash_.spend_all();
    cash_dispenser_ = CashDispenser();
}

void ATM::run(const Card *const p_card)
{
    // The customer inserted a card into the atm [TEST]
    if (!(handle_card_inserted(p_card)))
    {
        turn_off();
        return;
    }

    Message::display_menu("Session: " + session_.get_active_account()->get_name());
    // Instanciate a money object (ZERO DOLLARS) to hold the transaction amount
    Money in_transaction_money(0);

    bool valid_transaction = false;
    while (state_ == SERVING_CUSTOMER)
    {
        Message::display_menu("SELECT TRANSACTION TYPE");
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
        else
        {
            Message::display_content("Transaction processing failed...");
        }

        // Ask if the user wants to make another transaction
        if (!(customer_console_.get_new_transaction()))
        {
            set_state(IDLE);
            session_.reset_session();
            card_reader_.eject_card();
        }
    }
    return;
}

// Validate card, account, and initialize session
bool ATM::handle_card_inserted(const Card *const p_card)
{
    if (card_reader_.read_card(p_card))
    {
        // Get account to start the session
        Account *active_account = bank_DB_.get_account(card_reader_.get_card_number());
        if (session_.start_session(active_account))
        {
            // Validate session checking if the account isn't blocked and then prompt for the account PIN
            if (active_account->get_valid() && customer_console_.get_PIN(active_account->get_PIN()))
            {
                set_state(SERVING_CUSTOMER);
                return true;
            }
            else
            {
                // If too many invalid inputs for PIN
                card_reader_.retain_card();

                // Block the account associated with the card retained
                bank_DB_.block_account(active_account);
                bank_DB_.update_DB(bank_address_);
            }
        }
        return false;
    }
    else
    {
        // If fail to read card
        card_reader_.eject_card();
        return false;
    }
}

bool ATM::handle_deposit(Money *transaction_money)
{
    Message::display_menu("DEPOSIT");

    session_.get_active_account()->display();
    // Prompt for transaction money amount
    transaction_money->set_money(customer_console_.get_money());

    if (session_.start_transaction(DEPOSIT, transaction_money))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ATM::handle_withdraw(Money *transaction_money)
{
    Message::display_menu("WITHDRAW");

    session_.get_active_account()->display();
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
        {
            return false;
        }
    }
    else
    {
        std::cout << Message::content_sep_line()
                  << "Insuficient cash in the ATM cash dispenser.\nMaximum value for withdraw operations: "
                  << cash_dispenser_.get_cash_on_hand()->to_string()
                  << Message::content_sep_line();
        return false;
    }
}

bool ATM::handle_transfer(Money *transaction_money)
{
    Message::display_menu("TRANSFER");

    session_.get_active_account()->display();
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
    {
        return true;
    }
    else
    {
        return false;
    }
}