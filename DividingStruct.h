#pragma once

#include "SummingStruct.h"
#include "LeakedObjectDetector.h"

struct DividingStruct
{
    explicit DividingStruct(const SummingStruct&);

    ~DividingStruct();

    double divide() const;

    void modifyIntegers(unsigned int i);

    void printDivision();

    SummingStruct summing;
    SummingStruct::MultiplierStruct multiplier;

    JUCE_LEAK_DETECTOR(DividingStruct)
};
