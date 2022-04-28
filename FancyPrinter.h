#pragma once

#include "PivotString.h"
#include "LeakedObjectDetector.h"

struct FancyPrinter
{
public:
    FancyPrinter(const PivotString& pivot1, const PivotString& pivot2);

    ~FancyPrinter();

    void print() const;

    static void getParts(PivotString p, std::string& s1, std::string& s2);

private:
    PivotString p1, p2;

    JUCE_LEAK_DETECTOR(FancyPrinter)
};

