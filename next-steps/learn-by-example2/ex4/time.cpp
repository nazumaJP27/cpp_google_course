/* Example 4: Classes and objects (clock work).
Example run:
---------------------------------------------
Incrementing:
11:59:59 PM

12:00:00 AM

12:00:01 AM

12:00:02 AM

12:00:03 AM

Decrementing:
12:00:02 AM

12:00:01 AM

12:00:00 AM

11:59:59 PM

11:59:58 PM

---------------------------------------------
TODO:
Add a decrement method to this class (by example in `time-ex.cpp`). */

#include <iostream>

class Clock 
{
    int hours_, minutes_, seconds_;

public:
    void set(int h, int m, int s) { hours_ = h, minutes_ = m, seconds_ = s; }
    void increment();
    void decrement();
    void display();
};

void Clock::increment()
{
    seconds_++;
    minutes_ += seconds_ / 60;
    hours_ += minutes_ / 60;
    seconds_ %= 60;
    minutes_ %= 60;
    hours_ %= 24;
    return;
}

void Clock::decrement()
{
    if (--seconds_ < 0)
    {
        seconds_ = 59;
        if (--minutes_ < 0)
        {
            minutes_ = 59;
            if (--hours_ < 0)
            {
                hours_ = 23;
            }
        }
    }
    return;
}

void Clock::display()
{
    std::cout << (hours_ % 12 ? hours_ % 12 : 12) << ':'
              << (minutes_ < 10 ? "0" : "") << minutes_ << ':'
              << (seconds_ < 10 ? "0" : "") << seconds_
              << (hours_ < 12 ? " AM" : " PM") << std::endl;
}

int main()
{
    Clock timer;
    timer.set(23, 59, 58);

    std::cout << "Incrementing: "; timer.display();
    for (int i = 0; i < 5; i++)
    {
        timer.increment();
        timer.display();
        std::cout << std::endl;
    }

    std::cout << "Decrementing: "; timer.display();
    for (int i = 0; i < 5; i++)
    {
        timer.decrement();
        timer.display();
        std::cout << std::endl;
    }
}