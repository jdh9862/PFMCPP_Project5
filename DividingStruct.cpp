#include "DividingStruct.h"

DividingStruct::DividingStruct(const SummingStruct& s)
        : summing(s), multiplier(s)
{
}

DividingStruct::~DividingStruct()
{
    std::cout << "DividingStruct destroyed" << std::endl;
}

double DividingStruct::divide() const
{
    return this->multiplier.multiplyAll() / this->summing.sumAll();
}

void DividingStruct::modifyIntegers(unsigned int i)
{
    this->summing.setInteger(int(i));
    this->multiplier.incrementInteger(i);
}

void DividingStruct::printDivision() // FIXME: check for const-ness
{
std::cout << "divide " << (this->multiplier.integer ? "after" : "before") << " = " << this->divide() << std::endl;
}
