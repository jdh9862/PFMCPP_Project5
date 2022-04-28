#pragma once

#include <string>
#include "LeakedObjectDetector.h"

class PivotString
{
public:
    explicit PivotString(
            const std::string &string_,
            bool reversePivot_ = false,
            bool reverseString_ = false,
            unsigned long pivotIndex_ = 0);

    ~PivotString();

    std::string getPart(bool first = true);

    std::string getFull();

    std::string reverse(std::string string_);

    void printFull();

    int calls = 0;
    unsigned long pivotIndex;
    std::string string;
    bool reversePivot, reverseString;

    JUCE_LEAK_DETECTOR(PivotString)
};
