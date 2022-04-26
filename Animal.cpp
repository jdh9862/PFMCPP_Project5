#include <iostream>

#include "Animal.h"

Animal::Animal(std::string name_, unsigned int numberOfLegs_, bool canRun_)
        : name(std::move(name_)), numberOfLegs(numberOfLegs_)
{
    if (canRun_ && numberOfLegs_ < 2)
    {
        std::cout << "Animals " << this->name << " needs at least 2 legs to run"
                  << std::endl;
        this->canRun = false;
    }
    else
    {
        this->canRun = canRun_;
    }
}

Animal::~Animal()
{
    std::cout << "Animal " << this->name << " traveled " << this->feetTraveled << " feet"
              << std::endl;
}

void Animal::startRunning()
{
    if (canRun)
    {
        this->isRunning = true;
    }
    else
    {
        std::cout << "Animal " << this->name << " cannot run" << std::endl;
    }
}

void Animal::stopRunning()
{
    this->isRunning = false;
}

void Animal::travel(int numberOfSteps)
{
    if (this->numberOfLegs == 0)
    {
        std::cout << "Animal " << this->name
                  << " has no legs and rolls across the ground 1 foot"
                  << std::endl;
        ++feetTraveled;
        return;
    }
    unsigned int start = this->feetTraveled;
    for (int i = 0; i < numberOfSteps; ++i)
    {
        ++this->lastStep;
        if (this->lastStep >= this->numberOfLegs)
        {
            this->lastStep = 0;
            this->feetTraveled += this->isRunning ? 2 : 1;
        }
    }
    std::cout << "Animal " << this->name << " traveled " << (this->feetTraveled - start)
              << " feet in " << numberOfSteps << " steps" << std::endl;
}

Animal::Clock::Clock(bool is24Hour_) : is24Hour(is24Hour_)
{
    if (!is24Hour_)
    {
        this->hour = 12;
    }
}

Animal::Clock::~Clock()
{
    std::string suffix;
    if (!this->is24Hour)
    {
        suffix = this->isAM ? "AM" : "PM";
    }
    std::string mPrefix;
    if (this->minute < 10)
    {
        mPrefix = "0";
    }
    std::string sPrefix;
    if (this->second < 10)
    {
        sPrefix = "0";
    }
    std::cout << "The time is " << this->hour << ":" << mPrefix << this->minute << ":"
              << sPrefix << this->second << suffix << std::endl;
}

void Animal::Clock::incrementHour()
{
    ++this->hour;
    if (this->is24Hour)
    {
        if (this->hour == 24)
        {
            this->hour = 0;
        }
    }
    else
    {
        switch (this->hour)
        {
            case 12:
                this->isAM = !this->isAM;
                break;
            case 13:
                this->hour = 1;
                break;
        }
    }
}

void Animal::Clock::incrementMinute(bool silent)
{
    ++this->minute;
    if (this->minute == 60)
    {
        this->minute = 0;
        this->incrementHour();
        if (!silent)
        {
            int num = this->hour % 12;
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
    ++this->second;
    if (!silent)
    {
        std::cout << (this->second % 2 ? "tick" : "tock") << std::endl;
    }
    if (this->second == 60)
    {
        this->second = 0;
        this->incrementMinute(silent);
    }
}

void Animal::Clock::wind(
        unsigned int hours,
        unsigned int minutes,
        unsigned int seconds)
{
    for (unsigned int s = 0; s < seconds; ++s)
    {
        this->incrementSecond(true);
    }
    for (unsigned int m = 0; m < minutes; ++m)
    {
        this->incrementMinute(true);
    }
    for (unsigned int h = 0; h < hours; ++h)
    {
        this->incrementHour();
    }
}
