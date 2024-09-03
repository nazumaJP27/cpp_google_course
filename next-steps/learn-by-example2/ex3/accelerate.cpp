/* Example 3: Passing values by reference.
Example run:
---------------------------------------------
Maximum speed: 160.0
Current speed: 25.0
Accelerate by 52.7
Current speed: 77.7
---------------------------------------------
TODO:
Write a function called accelerate() that takes as input the speed of a vehicle, and an amount.
The function adds the amount to the speed to accelerate the vehicle.
The speed parameter should be passed by reference, and amount by value. */

#include <iostream>
#include <limits>

const float DIRT_BIKE_MAX = 160.0;

struct Vehicle
{
    float current_speed;
    float max_speed;

    // Constructor
    Vehicle(float current_speed=80.0, float max_speed=300.0) : current_speed(current_speed), max_speed(max_speed) {}
};

void accelerate(float &speed, float accel, float max);
float get_amount();

int main()
{
    // Create an instance of Vehicle
    Vehicle bike(25.0, DIRT_BIKE_MAX);
    
    // Print the maximum speed
    std::cout.precision(1);
    std::cout << std::fixed << "Maximum speed: " << bike.max_speed << "\nCurrent speed: " << bike.current_speed << std::endl;

    // Prompt for an amount to accelerate the vehicle
    float amount = get_amount();

    // Use the function to change the current speed of the object
    accelerate(bike.current_speed, amount, bike.max_speed);

    // Print current speed of the object
    std::cout << "Current speed: " << bike.current_speed << std::endl;

    return 0;
}

void accelerate(float &speed, float accel, float max) 
{
    speed += accel;
    if (speed > max) speed = max;
}

float get_amount()
{
    float input = 0;
    do 
    {
        std::cout << "Accelerate by ";
        if (!(std::cin >> input))
        {
            std::cin.clear();
            std::cout << "Input error... Enter a number digit.\n";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (input <= 0);

    return input;
}