#include <iostream>

#include "Animal.h"

Animal::Animal(std::string name_, unsigned int numberOfLegs_, bool canRun_) :
name(std::move(name_)),
numberOfLegs(numberOfLegs_)
{
    if (canRun_ && numberOfLegs_ < 2)
    {
        std::cout << "Animals " << name << " needs at least 2 legs to run"
                  << std::endl;
        canRun = false;
    }
    else
    {
        canRun = canRun_;
    }
}

Animal::~Animal()
{
    std::cout << "Animal " << name << " traveled " << feetTraveled << " feet"
              << std::endl;
}

void Animal::startRunning()
{
    if (canRun)
    {
        isRunning = true;
    }
    else
    {
        std::cout << "Animal " << name << " cannot run" << std::endl;
    }
}

void Animal::stopRunning()
{
    isRunning = false;
}

void Animal::travel(int numberOfSteps)
{
    if (numberOfLegs == 0)
    {
        std::cout << "Animal " << name
                  << " has no legs and rolls across the ground 1 foot"
                  << std::endl;
        ++feetTraveled;
        return;
    }
    unsigned int start = feetTraveled;
    for (int i = 0; i < numberOfSteps; ++i)
    {
        ++lastStep;
        if (lastStep >= numberOfLegs)
        {
            lastStep = 0;
            feetTraveled += isRunning ? 2 : 1;
        }
    }
    std::cout << "Animal " << name << " traveled " << (feetTraveled - start)
              << " feet in " << numberOfSteps << " steps" << std::endl;
}

Animal::Clock::Clock(bool is24Hour_) : is24Hour(is24Hour_)
{
    if (!is24Hour_)
    {
        hour = 12;
    }
}

Animal::Clock::~Clock()
{
    std::string suffix;
    if (!is24Hour)
    {
        suffix = isAM ? "AM" : "PM";
    }
    std::string mPrefix;
    if (minute < 10)
    {
        mPrefix = "0";
    }
    std::string sPrefix;
    if (second < 10)
    {
        sPrefix = "0";
    }
    std::cout << "The time is " << hour << ":" << mPrefix << minute << ":"
              << sPrefix << second << suffix << std::endl;
}

void Animal::Clock::incrementHour()
{
    ++hour;
    if (is24Hour)
    {
        if (hour == 24)
        {
            hour = 0;
        }
    }
    else
    {
        switch (hour)
        {
            case 12:
                isAM = !isAM;
                break;
            case 13:
                hour = 1;
                break;
        }
    }
}

void Animal::Clock::incrementMinute(bool silent)
{
    ++minute;
    if (minute == 60)
    {
        minute = 0;
        incrementHour();
        if (!silent)
        {
            int num = hour % 12;
            if (num == 0)
            {
                num = 12;
            }
            for (int i = 0; i < num; ++i)
            {
                std::cout << "Clang" << std::endl;
            }
        }
    }
}

void Animal::Clock::incrementSecond(bool silent)
{
    ++second;
    if (!silent)
    {
        std::cout << (second % 2 ? "tick" : "tock") << std::endl;
    }
    if (second == 60)
    {
        second = 0;
        incrementMinute(silent);
    }
}

void Animal::Clock::wind(
        unsigned int hours,
        unsigned int minutes,
        unsigned int seconds)
{
    for (unsigned int s = 0; s < seconds; ++s)
    {
        incrementSecond(true);
    }
    for (unsigned int m = 0; m < minutes; ++m)
    {
        incrementMinute(true);
    }
    for (unsigned int h = 0; h < hours; ++h)
    {
        incrementHour();
    }
}
