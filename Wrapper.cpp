#include "Wrapper.h"
#include "FancyPrinter.h"
#include "DividingStruct.h"

AnimalWrapper::AnimalWrapper::AnimalWrapper(Animal* ptr) : animalPtr(ptr) {}
AnimalWrapper::AnimalWrapper::~AnimalWrapper()
{
    delete animalPtr;
}

ClockWrapper::ClockWrapper(Animal::Clock* ptr) : clockPtr(ptr) {}
ClockWrapper::~ClockWrapper()
{
    delete clockPtr;
}

PivotStringWrapper::PivotStringWrapper(PivotString* ptr) : pivotStringPtr(ptr) {}
PivotStringWrapper::~PivotStringWrapper()
{
    delete pivotStringPtr;
}

SummingStructWrapper::SummingStructWrapper(SummingStruct* ptr) : summingStructPtr(ptr) {}
SummingStructWrapper::~SummingStructWrapper()
{
    delete summingStructPtr;
}

MultiplierStructWrapper::MultiplierStructWrapper(SummingStruct::MultiplierStruct* ptr) : multiplierStructPtr(ptr) {}
MultiplierStructWrapper::~MultiplierStructWrapper()
{
    delete multiplierStructPtr;
}

FancyPrinterWrapper::FancyPrinterWrapper(FancyPrinter* ptr) : fancyPrinterPtr(ptr) {}
FancyPrinterWrapper::~FancyPrinterWrapper()
{
    delete fancyPrinterPtr;
}

DividingStructWrapper::DividingStructWrapper(DividingStruct* ptr) : dividingStructPtr(ptr) {}
DividingStructWrapper::~DividingStructWrapper()
{
    delete dividingStructPtr;
}
