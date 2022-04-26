#include <iostream>
#include "PivotString.h"

PivotString::PivotString(
        const std::string &string_,
        bool reversePivot_,
        bool reverseString_,
        unsigned long pivotIndex_)
        : string(string_),
          reversePivot(reversePivot_),
          reverseString(reverseString_)
{
    this->pivotIndex = pivotIndex_ > string_.length()
                       ? string_.length() / 2
                       : pivotIndex_;
}

PivotString::~PivotString()
{
    std::cout << "PivotString " << this->getFull() << " was called " << this->calls
              << " times" << std::endl;
}

std::string PivotString::getPart(bool first)
{
    ++this->calls;
    return first
           ? this->string.substr(0, this->pivotIndex)
           : this->string.substr(this->pivotIndex, this->string.length() - this->pivotIndex);
}

std::string PivotString::getFull()
{
    ++this->calls;
    std::string first = this->getPart();
    std::string second = this->getPart(false);
    if (this->reverseString)
    {
        first = this->reverse(first);
        second = this->reverse(second);
    }
    return this->reversePivot ? second + first : first + second;
}

std::string PivotString::reverse(std::string string_)
{
    ++this->calls;
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
