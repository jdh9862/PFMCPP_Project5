#include <iostream>
#include "PivotString.h"

PivotString::PivotString(const std::string &string_, bool reversePivot_, bool reverseString_, unsigned long pivotIndex_) :
string(string_),
reversePivot(reversePivot_),
reverseString(reverseString_)
{
    pivotIndex = pivotIndex_ > string_.length() ? string_.length() / 2 : pivotIndex_;
}

PivotString::~PivotString()
{
    std::cout << "PivotString " << getFull() << " was called " << calls
              << " times" << std::endl;
}

std::string PivotString::getPart(bool first)
{
    ++calls;
    return first
           ? string.substr(0, pivotIndex)
           : string.substr(pivotIndex, string.length() - pivotIndex);
}

std::string PivotString::getFull()
{
    ++calls;
    std::string first = getPart();
    std::string second = getPart(false);
    if (reverseString)
    {
        first = reverse(first);
        second = reverse(second);
    }
    return reversePivot ? second + first : first + second;
}

std::string PivotString::reverse(std::string string_)
{
    ++calls;
    std::string reversed;
    while (reversed.length() < string_.length())
    {
        unsigned long i = string_.length() - reversed.length() - 1;
        reversed.push_back(string_[i]);
    }
    return reversed;
}

void PivotString::printFull()
{
    std::cout << "PivotString " << this->string << " = " << this->getFull() << std::endl;
}
