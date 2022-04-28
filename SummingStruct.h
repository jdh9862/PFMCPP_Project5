#pragma once

#include "LeakedObjectDetector.h"

struct SummingStruct
{
    SummingStruct(float first, float second);

    ~SummingStruct();

    void setInteger(int newValue);

    double sumAll() const;

    float sumFloats() const;

    void printSum(bool onlyFloats);

    int integer = 0;
    double firstDouble, secondDouble;
    float firstFloat, secondFloat;

    struct MultiplierStruct
    {
        explicit MultiplierStruct(const SummingStruct& summingStruct);

        ~MultiplierStruct();

        void incrementInteger(unsigned int added);

        double multiplyAll() const;

        float multiplyFloats() const;

        void printMultiply(bool onlyFloats);

        int integer = 0;
        double firstDouble, secondDouble;
        float firstFloat, secondFloat;

        JUCE_LEAK_DETECTOR(SummingStruct::MultiplierStruct)
    };

    JUCE_LEAK_DETECTOR(SummingStruct)
};
