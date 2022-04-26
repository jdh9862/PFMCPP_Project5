#include "SummingStruct.h"

SummingStruct::SummingStruct(float first, float second)
        : firstDouble(static_cast<double>(first)),
          secondDouble(static_cast<double>(second)),
          firstFloat(first),
          secondFloat(second)
{
}

SummingStruct::~SummingStruct()
{
    std::cout << "SummingStruct destroyed" << std::endl;
}

void SummingStruct::setInteger(int newValue)
{
    this->integer = 0;
    while (this->integer < abs(newValue))
    {
        ++this->integer;
    }
}

double SummingStruct::sumAll() const
{
    return double(this->sumFloats()) + this->firstDouble + this->secondDouble + this->integer;
}

float SummingStruct::sumFloats() const
{
    return this->firstFloat + this->secondFloat;
}

void SummingStruct::printSum(bool onlyFloats)
{
    if (onlyFloats)
    {
        std::cout << "sumFloats = " << this->sumFloats() << std::endl;
    }
    else
    {
        std::cout << "sumAll = " << this->sumAll() << std::endl;
    }
}

SummingStruct::MultiplierStruct::MultiplierStruct(
        const SummingStruct& summingStruct)
: firstDouble(summingStruct.firstDouble),
secondDouble(summingStruct.secondDouble),
firstFloat(summingStruct.firstFloat),
secondFloat(summingStruct.secondFloat)
{
}

SummingStruct::MultiplierStruct::~MultiplierStruct()
{
    std::cout << "MultiplierStruct destroyed" << std::endl;
}

void SummingStruct::MultiplierStruct::incrementInteger(unsigned int added)
{
    while (added > 0)
    {
        --added;
        ++this->integer;
    }
}

double SummingStruct::MultiplierStruct::multiplyAll() const
{
    return double(multiplyFloats()) * this->firstDouble * this->secondDouble * this->integer;
}

float SummingStruct::MultiplierStruct::multiplyFloats() const
{
    return this->firstFloat * this->secondFloat;
}

void SummingStruct::MultiplierStruct::printMultiply(bool onlyFloats)
{
    if (onlyFloats)
    {
        std::cout << "multiplyFloats = " << this->multiplyFloats()
                  << std::endl;
    }
    else
    {
        std::cout << "multiplyAll = " << this->multiplyAll() << std::endl;
    }
}
