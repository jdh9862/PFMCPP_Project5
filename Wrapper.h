#include "Animal.h"
#include "FancyPrinter.h"
#include "DividingStruct.h"

struct AnimalWrapper
{
    AnimalWrapper(Animal* ptr);
    ~AnimalWrapper();

    Animal* animalPtr;
};

struct ClockWrapper
{
    ClockWrapper(Animal::Clock* ptr);
    ~ClockWrapper();

    Animal::Clock* clockPtr;
};

struct PivotStringWrapper
{
    PivotStringWrapper(PivotString* ptr);
    ~PivotStringWrapper();

    PivotString* pivotStringPtr;
};

struct SummingStructWrapper
{
    SummingStructWrapper(SummingStruct* ptr);
    ~SummingStructWrapper();

    SummingStruct* summingStructPtr;
};

struct MultiplierStructWrapper
{
    MultiplierStructWrapper(SummingStruct::MultiplierStruct* ptr);
    ~MultiplierStructWrapper();

    SummingStruct::MultiplierStruct* multiplierStructPtr;
};

struct FancyPrinterWrapper
{
    FancyPrinterWrapper(FancyPrinter* ptr);
    ~FancyPrinterWrapper();

    FancyPrinter* fancyPrinterPtr;
};

struct DividingStructWrapper
{
    DividingStructWrapper(DividingStruct* ptr);
    ~DividingStructWrapper();

    DividingStruct* dividingStructPtr;
};
