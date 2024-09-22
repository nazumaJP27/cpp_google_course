#pragma once

#include "OperatorPanel.h"
#include "CardReader.h"
#include "CashDispenser.h"
#include "Money.h"
#include "Account.h"
#include "BankDB.h"
#include <iostream>
#include <string>

enum ATM_State
{
    OFF = 0, IDLE, SERVING_CUSTOMER
};

// Default CSV file with test accounts (card number,card flag,person,balance)
static const std::string DEFAULT_ACCOUNTS = "accounts.csv";

class ATM
{
    // Member variables
    ATM_State state_;
    int id_;
    std::string place_;
    std::string bank_name;
    std::string bank_address_; // Probably will be a path to a CSV
    bool card_inserted_;
    Money initial_cash_;

    // Member objects
public:
    OperatorPanel operator_panel_;
    CardReader card_reader_;
    CashDispenser cash_dispenser_;
    BankDB bank_DB_;

public:
    // Constructor
    ATM(int id, const std::string place, const std::string bank_name, std::string bank_address=DEFAULT_ACCOUNTS);

    // Methods
    void run();

    // Methods 
    void turn_on();
    void turn_off();
    void card_inserted();

    // Assesors
    ATM_State get_state() const { return state_; };
    int get_id() const { return id_; }
    std::string get_place() const { return place_; }
    std::string get_bank_name() const { return bank_name; }
    std::string get_bank_address() const { return bank_address_; }
    const Money* get_initial_cash() const { return &initial_cash_; }
    bool get_card_inserted() const { return card_inserted_; }

    // Mutator
    void set_bank_address(std::string address) { bank_address_ = address; }

private:
    void perform_startup();
    void perform_shutdown();

};