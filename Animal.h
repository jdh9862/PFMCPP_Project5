#pragma once

#include <string>
#include "LeakedObjectDetector.h"

class Animal
{
public:
    Animal(std::string name_, unsigned int numberOfLegs_, bool canRun_ = false);

    ~Animal();

    void startRunning();

    void stopRunning();

    void travel(int numberOfSteps);

    class Clock
    {
    public:
        explicit Clock(bool is24Hour_);

        ~Clock();

        void incrementHour();

        void incrementMinute(bool silent = false);

        void incrementSecond(bool silent = false);

        void
        wind(unsigned int hours, unsigned int minutes, unsigned int seconds);

    private:
        bool is24Hour, isAM = true;
        int hour = 0, minute = 0, second = 0;

        JUCE_LEAK_DETECTOR(Animal::Clock)
    };

private:
    std::string name;
    unsigned int numberOfLegs, lastStep = 0, feetTraveled = 0;
    bool canRun, isRunning = false;
    JUCE_LEAK_DETECTOR(Animal)
};
