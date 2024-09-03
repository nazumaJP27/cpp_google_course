/* Consider the following output from a simple game:
---------------------------------------------
Welcome to Artillery.
You are in the middle of a war and being charged by thousands of enemies.
You have one cannon, which you can shoot at any angle.
You only have 10 cannonballs for this target..
Let's begin...

The enemy is 507 feet away!!!
What angle? 25<
You over shot by 445
What angle? 15
You over shot by 114
What angle? 10
You under shot by 82
What angle? 12
You under shot by 2
What angle? 12.01
You hit him!!!
It took you 4 shots.
You have killed this enemy.
I see another one, are you ready? (Y/N) n

You killed 1 of the enemy.
---------------------------------------------
TODO: Try writing this program.*/

/* STEPS:
#0. Print the introduction of the game.
#1. Initialize a game: define the enemy distance using a random number generator, and reset the number of cannonballs to 10.
#2. Prompt the player on each round to get an angle input for firing the cannon.
#3. Calculate where the cannonball hit and return the distance.
#4. Check if the cannonball hit the enemy -- output: "You hit him!!!" || "You over/under shot by [diference in distance]".
#5. If the player hit the target, output: "It took you [shots taken] shots",
    prompt for reseting the game [go back to step 1] or end the program [go to last step].
#5.5 Else (i.e., miss the target) proceed to the next step.
#6. Check if there are still cannonballs left to shoot; begin another round [go back to step 2] || output: "Out of cannonballs!"
#7. Display the number of enemies killed by the player and end the program. */

#include <algorithm> // std::remove_if, std::transform
#include <iostream>
#include <limits>    // std::numeric_limits
#include <math.h>    // sin, cos
#include <stdlib.h>  // srand, rand
#include <string>
#include <time.h>    // time

// Constants
const float PI = 3.1415;             // pi
const double VELOCITY = 200.0; // Initial velocity for the cannonball of 200 ft/sec
const double GRAVITY = 32.2;   // Gravity for distance calculation
const int MAX_DISTANCE = (VELOCITY * VELOCITY) / GRAVITY;

// Classes and Structs
class Enemy
{
    bool alive;
    int distance;

public:
    // Constructor
    Enemy() : alive(true), distance(rand() % MAX_DISTANCE) {}

    int get_distance() { return distance; }
    bool is_alive() { return alive; }
    void killed() { alive = false; }
    void reset()
    {
        alive = true;
        distance = rand() % MAX_DISTANCE;
    }
};

struct GameVars
{
    unsigned int enemies_killed = 0;
    unsigned int cannonballs = 10;
    unsigned int shots_taken = 0;
    std::string play = "Yes"; // Anything will work realy, the game loop will check for 'n' or "no".

    void reset() { cannonballs = 10; shots_taken = 0; }
};

// Prototypes
void clean_string(std::string &input);
void fire_cannon(GameVars &game_vars, Enemy &enemy);
double get_angle(const std::string &prompt="Angle: ");
bool play_again(const std::string &prompt="Play again? ");
void reset_game(GameVars &game_vars, Enemy &enemy);
int distance(double angle);
void start_up_message();

int main()
{
    srand(time(nullptr)); // Seed the random number generator

    // #0: Display the introdutory script
    start_up_message();

    // Create a GameVars and Enemy instance
    GameVars game_vars;
    Enemy enemy;

    do
    {
        // #1: Initialize the game state
        reset_game(game_vars, enemy);
        std::cout << "-----------------------------------------------\n"
                  << "You only have " << game_vars.cannonballs << " cannonballs for this target...\n"
                  << "Let's begin..." << std::endl;

        // #2 Display the distance of the enemy and begin the game loop
        std::cout << "\nThe enemy is " << enemy.get_distance() << " feet away!!!" << std::endl;
        fire_cannon(game_vars, enemy);

        // Prompt for another round
    } while (play_again("I see another one, are you ready? ") == true);
    
    // #7 Display the number of enemies killed by the player
    std::cout << "\nYou killed " << game_vars.enemies_killed << " of the enemy." << std::endl;

    return 0; 
}

void start_up_message()
{
    std::cout << "Welcome to artillery.\n"
              << "You are in the middle of a war and being charged by thousands of enemies.\n"
              << "You have one cannon, which you can shoot at any angle." << std::endl;
}

void reset_game(GameVars &game_vars, Enemy &enemy)
{
    game_vars.reset();
    enemy.reset();
}

// Main loop of each round
void fire_cannon(GameVars &game_vars, Enemy &enemy)
{
    float in_angle = 0;
    int shot_distance = 0, difference = 0;
    int enemy_distance = enemy.get_distance();

    while(enemy.is_alive() && game_vars.cannonballs > 0)
    {
        // Prompt for angle of shot
        in_angle = get_angle("What angle? ");

        // #3 Update game variables and calculate the distance of the shot
        game_vars.cannonballs--;
        game_vars.shots_taken++;
        shot_distance = distance(in_angle);

        // #4 Check if the cannonball hit the enemy
        difference = shot_distance - enemy_distance;

        if (difference > 1)
        {
            std::cout << "You over shot by " << difference << std::endl;
        }
        else if (difference < -1)
        {
            std::cout << "You under shot by " << -difference << std::endl;
        }
        else
        {
            enemy.killed();
            game_vars.enemies_killed++;
            std::cout << "You hit him!!!\nIt took you " << game_vars.shots_taken << " shots." << std::endl;
        }
    }
    
    // Check if the enemy was killed and display a message on the console
    if (enemy.is_alive())
        std::cout << "Out of cannonballs!\nThe enemy has scaped... Better luck next time.\n";
    else
        std::cout << "You have killed this enemy.\n";

    std::cout << "-----------------------------------------------\n";
}

// Prompt [custom prompt] for angle, validate, and return input as int
double get_angle(const std::string &prompt)
{
    double input = 0.0;
    do
    {
        std::cout << prompt;
        if (!(std::cin >> input))
        {
            std::cin.clear();
            std::cout << "Invalid input...\nEnter an angle containing only number digits." << std::endl;
        }
        else if (input >= 90)
        {
            std::cout << "Don't shoot backwards. Enter an angle less than 90 degrees" << std::endl;
            input = 0;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (input <= 0);

    return input;
}

// Calculate the distance of a shot using the in_angle radians
int distance(double in_angle)
{
    double angle = (in_angle * PI) / 180.0; // Convert in_angle to radians
    double time_in_air = (2.0 * VELOCITY * sin(angle)) / GRAVITY;
    return (int) round((VELOCITY * cos(angle)) * time_in_air);
}

// Prompt [custom prompt], validate, and return bool
bool play_again(const std::string &prompt)
{
    std::string input;
    do
    {
        std::cout << prompt << "(Y/N) ";
        std::cin >> input; 
        clean_string(input);

        if (input == "n" || input == "no" || input == "end" || input == "quit")
            return false;
        else if (input == "y" || input == "yes")
            return true;
        else
            std::cout << "Invalid input...\nEnter 'Y/Yes' to play another round, or 'N/No/End/Quit' to close the game." << std::endl;
        // Clear input buffer and input variable
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        input.clear();
    } while (input.empty());

    // Never gets here
    return true;
}

// Remove '<', '>', '^', '.' chars and lower case input string
void clean_string(std::string &input)
{
    std::string::iterator new_end = std::remove_if(input.begin(), input.end(), [](char c)
    { return c == '<' || c == '>' || c == '^' || c == '.' || c == ','; });
    input.erase(new_end, input.end());

    // Lower case all chars in string
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
}