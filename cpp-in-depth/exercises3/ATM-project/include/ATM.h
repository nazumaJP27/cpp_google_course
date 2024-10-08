#pragma once

#include "OperatorPanel.h"
#include "CardReader.h"
#include "CashDispenser.h"
#include "Money.h"
#include "Account.h"
#include "BankDB.h"
#include "Session.h"
#include "CustomerConsole.h"
#include "Message.h"

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
    std::string bank_name_;
    std::string bank_address_;
    Money initial_cash_;

    // Member objects
    OperatorPanel operator_panel_;
    CardReader card_reader_;
    CashDispenser cash_dispenser_;
    BankDB bank_DB_;
    Session session_;
    CustomerConsole customer_console_;

public:
    // Constructor
    ATM();
    ATM(int id, const std::string place, const std::string bank_name, std::string bank_address=DEFAULT_ACCOUNTS);

    // Methods 
    void turn_on();
    void turn_off();
    void run(const Card *const p_card);

    // Assesors
    ATM_State get_state() const { return state_; };
    int get_id() const { return id_; }
    const std::string& get_place() const { return place_; }
    const std::string& get_bank_name() const { return bank_name_; }
    const std::string& get_bank_address() const { return bank_address_; }
    const Money* get_initial_cash() const { return &initial_cash_; }

    // Mutator
    void set_id(int id) { id_ = id; }
    void set_place(const std::string &place) { place_ = place; }
    void set_bank_name(const std::string &bank_name) { bank_name_ = bank_name; }
    void set_bank_address(const std::string &address) { bank_address_ = address; }
    void set_state(ATM_State state) { state_ = state; }

private:
    void perform_startup();
    void perform_shutdown();
    bool handle_card_inserted(const Card *const p_card);
    bool handle_deposit(Money *transaction_money);
    bool handle_withdraw(Money *transaction_money);
    bool handle_transfer(Money *transaction_money);
};