#pragma once

#include <string>

enum ATM_State
{
    OFF = 0, IDLE, SERVING_CUSTOMER
};

class ATM
{
    ATM_State state_;
    int id_;
    std::string place_;
    std::string bank_;
    std::string bank_address_; // Probably will be a path to a CSV
    //OperatorPanel operator_panel_;

public:
    // Constructor
    ATM(int id, std::string place, std::string bank);

    // Methods
    void run();

    // Methods (for the operator) 
    void turn_on();
    void turn_off();

    // Assesors
    ATM_State get_state_() { return state_; };
    int get_id() { return id_; }    
    std::string get_place() { return place_; }
    std::string get_bank() { return bank_; }
    std::string get_bank_address() { return bank_address_; }

private:
    void perform_startup();
    void perform_shutdown();

};