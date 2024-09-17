#pragma once

#include "OperatorPanel.h"
#include "CardReader.h"
#include <iostream>
#include <string>

enum ATM_State
{
    OFF = 0, IDLE, SERVING_CUSTOMER
};

class ATM
{
    // Member variables
    ATM_State state_;
    int id_;
    std::string place_;
    std::string bank_;
    std::string bank_address_; // Probably will be a path to a CSV
    double initial_cash_;

    // Member objects
    OperatorPanel operator_panel_;
    CardReader card_reader_;

public:
    // Constructor
    ATM(int id, std::string place, std::string bank);

    // Methods
    void run();

    // Methods (for the operator) 
    void turn_on();
    void turn_off();

    // Assesors
    ATM_State get_state_() const { return state_; };
    int get_id() const { return id_; }
    std::string get_place() const { return place_; }
    std::string get_bank() const { return bank_; }
    std::string get_bank_address() const { return bank_address_; }
    double get_initial_cash() const { return initial_cash_; }

private:
    void perform_startup();
    void perform_shutdown();

};