/*
 Project 5: Part 3 / 4
 video: Chapter 3 Part 4: 

Create a branch named Part3

 the 'new' keyword

 1) add #include "LeakedObjectDetector.h" to main
 
 2) Add 'JUCE_LEAK_DETECTOR(OwnerClass)' at the end of your UDTs.
 
 3) write the name of your class where it says "OwnerClass"
 
 4) write wrapper classes for each type similar to how it was shown in the video
 
 5) update main() 
      replace your objects with your wrapper classes, which have your UDTs as pointer member variables.
      
    This means if you had something like the following in your main() previously: 
*/
#if false
 Axe axe;
 std::cout << "axe sharpness: " << axe.sharpness << "\n";
 #endif
 /*
    you would update that to use your wrappers:
    
 */

#if false
AxeWrapper axWrapper( new Axe() );
std::cout << "axe sharpness: " << axWrapper.axPtr->sharpness << "\n";
#endif
/*
notice that the object name has changed from 'axe' to 'axWrapper'
You don't have to do this, you can keep your current object name and just change its type to your Wrapper class

6) If you have a class that has a nested class in it, and an instantiation of that nested class as a member variable, 
    - you do not need to write a Wrapper for that nested class
    - you do not need to replace that nested instance with a wrapped instance.
    If you want an explanation, message me in Slack

7) If you were using any UDTs as function arguments like this:
*/
#if false
void someMemberFunction(Axe axe);
#endif
/*
  Pass those arguments by Reference now that you know what references are (Project 6 Part 2).
*/
#if false
void someMemberFunction(Axe& axe);
#endif
/*
If you aren't modifying the passed-in object inside the function, pass by 'const reference'.
Marking a function parameter as 'const' means that you are promising that the parameter will not be modified.
Additionally, you can mark class member functions as 'const'
If you do this, you are promising that the member function will not modify any member variables.

Mark every member function that is not modifying any member variables as 'const'
*/
#if false
//a function where the argument is passed by const-ref
void someMemberFunction(const Axe& axe);

//a member function that is marked const, meaning it will not modify any member variables of the 'Axe' class.
void Axe::aConstMemberFunction() const { }
#endif
/*
 8) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 
 see here for an example: https://repl.it/@matkatmusic/ch3p04example

 Clear any warnings about exit-time-destructors.
 Suppress them by adding -Wno-exit-time-destructors to the .replit file with the other warning suppression flags
 */





#include <iostream>
#include <utility>

/*
 copied UDT 1:
 */
class Animal
{
public:
    Animal(std::string name_, unsigned int numberOfLegs_, bool canRun_ = false);

    ~Animal();

    void startRunning();

    void stopRunning();

    void travel(int numberOfSteps);

    class Clock
    {
    public:
        explicit Clock(bool is24Hour_);

        ~Clock();

        void incrementHour();

        void incrementMinute(bool silent = false);

        void incrementSecond(bool silent = false);

        void
        wind(unsigned int hours, unsigned int minutes, unsigned int seconds);

    private:
        bool is24Hour, isAM = true;
        int hour = 0, minute = 0, second = 0;
    };

private:
    std::string name;
    unsigned int numberOfLegs, lastStep = 0, feetTraveled = 0;
    bool canRun, isRunning = false;
};

Animal::Animal(std::string name_, unsigned int numberOfLegs_, bool canRun_)
        : name(std::move(name_)), numberOfLegs(numberOfLegs_)
{
    if (canRun_ && numberOfLegs_ < 2)
    {
        std::cout << "Animals " << this->name << " needs at least 2 legs to run"
                  << std::endl;
        this->canRun = false;
    }
    else
    {
        this->canRun = canRun_;
    }
}

Animal::~Animal()
{
    std::cout << "Animal " << this->name << " traveled " << this->feetTraveled << " feet"
              << std::endl;
}

void Animal::startRunning()
{
    if (canRun)
    {
        this->isRunning = true;
    }
    else
    {
        std::cout << "Animal " << this->name << " cannot run" << std::endl;
    }
}

void Animal::stopRunning()
{
    this->isRunning = false;
}

void Animal::travel(int numberOfSteps)
{
    if (this->numberOfLegs == 0)
    {
        std::cout << "Animal " << this->name
                  << " has no legs and rolls across the ground 1 foot"
                  << std::endl;
        ++feetTraveled;
        return;
    }
    unsigned int start = this->feetTraveled;
    for (int i = 0; i < numberOfSteps; ++i)
    {
        ++this->lastStep;
        if (this->lastStep >= this->numberOfLegs)
        {
            this->lastStep = 0;
            this->feetTraveled += this->isRunning ? 2 : 1;
        }
    }
    std::cout << "Animal " << this->name << " traveled " << (this->feetTraveled - start)
              << " feet in " << numberOfSteps << " steps" << std::endl;
}

struct AnimalWrapper
{
    AnimalWrapper(Animal *ptr) : animalPtr(ptr) {}
    ~AnimalWrapper()
    {
        delete animalPtr;
    }

    Animal* animalPtr;
};

Animal::Clock::Clock(bool is24Hour_) : is24Hour(is24Hour_)
{
    if (!is24Hour_)
    {
        this->hour = 12;
    }
}

Animal::Clock::~Clock()
{
    std::string suffix;
    if (!this->is24Hour)
    {
        suffix = this->isAM ? "AM" : "PM";
    }
    std::string mPrefix;
    if (this->minute < 10)
    {
        mPrefix = "0";
    }
    std::string sPrefix;
    if (this->second < 10)
    {
        sPrefix = "0";
    }
    std::cout << "The time is " << this->hour << ":" << mPrefix << this->minute << ":"
              << sPrefix << this->second << suffix << std::endl;
}

void Animal::Clock::incrementHour()
{
    ++this->hour;
    if (this->is24Hour)
    {
        if (this->hour == 24)
        {
            this->hour = 0;
        }
    }
    else
    {
        switch (this->hour)
        {
            case 12:
                this->isAM = !this->isAM;
                break;
            case 13:
                this->hour = 1;
                break;
        }
    }
}

void Animal::Clock::incrementMinute(bool silent)
{
    ++this->minute;
    if (this->minute == 60)
    {
        this->minute = 0;
        this->incrementHour();
        if (!silent)
        {
            int num = this->hour % 12;
            if (num == 0)
            {
                num = 12;
            }
            for (int i = 0; i < num; ++i)
            {
                std::cout << "Clang" << std::endl;
            }
        }
    }
}

void Animal::Clock::incrementSecond(bool silent)
{
    ++this->second;
    if (!silent)
    {
        std::cout << (this->second % 2 ? "tick" : "tock") << std::endl;
    }
    if (this->second == 60)
    {
        this->second = 0;
        this->incrementMinute(silent);
    }
}

void Animal::Clock::wind(
        unsigned int hours,
        unsigned int minutes,
        unsigned int seconds)
{
    for (unsigned int s = 0; s < seconds; ++s)
    {
        this->incrementSecond(true);
    }
    for (unsigned int m = 0; m < minutes; ++m)
    {
        this->incrementMinute(true);
    }
    for (unsigned int h = 0; h < hours; ++h)
    {
        this->incrementHour();
    }
}

struct ClockWrapper
{
    ClockWrapper(Animal::Clock *ptr) : clockPtr(ptr) {}
    ~ClockWrapper()
    {
        delete clockPtr;
    }

    Animal::Clock* clockPtr;
};

/*
 copied UDT 2:
 */
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
};

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

struct PivotStringWrapper
{
    PivotStringWrapper(PivotString *ptr) : pivotStringPtr(ptr) {}
    ~PivotStringWrapper()
    {
        delete pivotStringPtr;
    }

    PivotString* pivotStringPtr;
};

/*
 copied UDT 3:
 */
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
        explicit MultiplierStruct(const SummingStruct &summingStruct);

        ~MultiplierStruct();

        void incrementInteger(unsigned int added);

        double multiplyAll() const;

        float multiplyFloats() const;

        void printMultiply(bool onlyFloats);

        int integer = 0;
        double firstDouble, secondDouble;
        float firstFloat, secondFloat;
    };
};

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

struct SummingStructWrapper
{
    SummingStructWrapper(SummingStruct *ptr) : summingStructPtr(ptr) {}
    ~SummingStructWrapper()
    {
        delete summingStructPtr;
    }

    SummingStruct* summingStructPtr;
};

SummingStruct::MultiplierStruct::MultiplierStruct(
        const SummingStruct &summingStruct)
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

struct MultiplierStructWrapper
{
    MultiplierStructWrapper(SummingStruct::MultiplierStruct *ptr) : multiplierStructPtr(ptr) {}
    ~MultiplierStructWrapper()
    {
        delete multiplierStructPtr;
    }

    SummingStruct::MultiplierStruct* multiplierStructPtr;
};

/*
 new UDT 4:
 with 2 member functions
 */
struct FancyPrinter
{
public:
    FancyPrinter(const PivotString &pivot1, const PivotString &pivot2);

    ~FancyPrinter();

    void print() const;

    static void getParts(PivotString p, std::string &s1, std::string &s2);

private:
    PivotString p1, p2;
};

FancyPrinter::FancyPrinter(const PivotString &pivot1, const PivotString &pivot2)
        : p1(pivot1), p2(pivot2)
{
}

FancyPrinter::~FancyPrinter()
{
    std::cout << "FancyPrinter called it's PivotStrings "
              << this->p1.calls + this->p2.calls << " times" << std::endl;
}

void FancyPrinter::print() const
{
    std::string s1, s2, s3, s4;
    getParts(this->p1, s1, s3);
    getParts(this->p2, s2, s4);
    std::cout << s1 << s2 << s3 << s4 << std::endl;
}

void FancyPrinter::getParts(PivotString p, std::string &s1, std::string &s2)
{
    if (p.reversePivot)
    {
        s1 = p.getPart(false);
        s2 = p.getPart();
    }
    else
    {
        s1 = p.getPart();
        s2 = p.getPart(false);
    }
    if (p.reverseString)
    {
        s1 = p.reverse(s1);
        s2 = p.reverse(s2);
    }
}

struct FancyPrinterWrapper
{
    FancyPrinterWrapper(FancyPrinter *ptr) : fancyPrinterPtr(ptr) {}
    ~FancyPrinterWrapper()
    {
        delete fancyPrinterPtr;
    }

    FancyPrinter* fancyPrinterPtr;
};

/*
 new UDT 5:
 with 2 member functions
 */
struct DividingStruct
{
    explicit DividingStruct(const SummingStruct &);

    ~DividingStruct();

    double divide() const;

    void modifyIntegers(unsigned int i);

    void printDivision();

    SummingStruct summing;
    SummingStruct::MultiplierStruct multiplier;
};

DividingStruct::DividingStruct(const SummingStruct &s)
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

void DividingStruct::printDivision()
{
    std::cout << "divide " << (this->multiplier.integer ? "after" : "before") << " = " << this->divide() << std::endl;
}

struct DividingStructWrapper
{
    DividingStructWrapper(DividingStruct *ptr) : dividingStructPtr(ptr) {}
    ~DividingStructWrapper()
    {
        delete dividingStructPtr;
    }

    DividingStruct* dividingStructPtr;
};

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left,
 entering a message, and click [Commit and push].

 If you didn't already:
	Make a pull request after you make your first commit
	pin the pull request link and this repl.it link to our DM thread in a single
 message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

int main()
{
    AnimalWrapper pogoFrog{new Animal("Pogo Frog", 1, true)};
    pogoFrog.animalPtr->travel(2);
    pogoFrog.animalPtr->startRunning();
    pogoFrog.animalPtr->travel(2);
    pogoFrog.animalPtr->stopRunning();
    pogoFrog.animalPtr->travel(1);

    AnimalWrapper fishOutOfWater{new Animal("Fish", 0)};
    fishOutOfWater.animalPtr->travel(2);
    fishOutOfWater.animalPtr->startRunning();
    fishOutOfWater.animalPtr->travel(2);
    fishOutOfWater.animalPtr->stopRunning();
    fishOutOfWater.animalPtr->travel(1);

    AnimalWrapper dog{new Animal("Dog", 4, true)};
    dog.animalPtr->travel(2);
    dog.animalPtr->startRunning();
    dog.animalPtr->travel(2);
    dog.animalPtr->stopRunning();
    dog.animalPtr->travel(1);
    std::cout << std::endl;

    ClockWrapper clock1{new Animal::Clock(true)};
    clock1.clockPtr->wind(23, 59, 59);
    clock1.clockPtr->incrementSecond();
    clock1.clockPtr->incrementSecond();
    std::cout << std::endl;

    ClockWrapper clock2{new Animal::Clock(false)};
    clock2.clockPtr->wind(12, 59, 58);
    clock2.clockPtr->incrementSecond();
    clock2.clockPtr->incrementSecond();
    std::cout << std::endl;

    PivotStringWrapper simple{new PivotString("simple")};
    PivotStringWrapper reversed{new PivotString("reversed", true, true)};
    PivotStringWrapper mangled{new PivotString("mangled", false, true, 100)};
    PivotStringWrapper first{new PivotString("first", true, false, 1)};
    PivotStringWrapper last{new PivotString("last", true, false, 4)};
    std::cout << "PivotString simple = " << simple.pivotStringPtr->getFull() << std::endl;
    simple.pivotStringPtr->printFull();
    std::cout << "PivotString reversed = " << reversed.pivotStringPtr->getFull() << std::endl;
    reversed.pivotStringPtr->printFull();
    std::cout << "PivotString mangled = " << mangled.pivotStringPtr->getFull() << std::endl;
    mangled.pivotStringPtr->printFull();
    std::cout << "PivotString first = " << first.pivotStringPtr->getFull() << std::endl;
    first.pivotStringPtr->printFull();
    std::cout << "PivotString last = " << last.pivotStringPtr->getFull() << std::endl;
    last.pivotStringPtr->printFull();
    std::cout << std::endl;

    SummingStructWrapper summing{new SummingStruct(1.1f, 2.0f)};
    summing.summingStructPtr->setInteger(-2);
    std::cout << "sumFloats = " << summing.summingStructPtr->sumFloats() << std::endl;
    summing.summingStructPtr->printSum(true);
    std::cout << "sumAll = " << summing.summingStructPtr->sumAll() << std::endl;
    summing.summingStructPtr->printSum(false);
    std::cout << std::endl;

    MultiplierStructWrapper multiplier{new SummingStruct::MultiplierStruct(*summing.summingStructPtr)};
    multiplier.multiplierStructPtr->incrementInteger(3);
    std::cout << "multiplyFloats = " << multiplier.multiplierStructPtr->multiplyFloats()
              << std::endl;
    multiplier.multiplierStructPtr->printMultiply(true);
    std::cout << "multiplyAll = " << multiplier.multiplierStructPtr->multiplyAll() << std::endl;
    multiplier.multiplierStructPtr->printMultiply(false);
    std::cout << std::endl;

    FancyPrinterWrapper p{new FancyPrinter(*simple.pivotStringPtr, *mangled.pivotStringPtr)};
    p.fancyPrinterPtr->print();
    std::cout << std::endl;

    DividingStructWrapper divider{new DividingStruct(*summing.summingStructPtr)};
    // Result will be zero because the multiplier's integer has not been
    // incremented
    std::cout << "divide before = " << divider.dividingStructPtr->divide() << std::endl;
    divider.dividingStructPtr->printDivision();
    divider.dividingStructPtr->modifyIntegers(1);
    std::cout << "divide after = " << divider.dividingStructPtr->divide() << std::endl;
    divider.dividingStructPtr->printDivision();
    std::cout << std::endl;

    std::cout << "good to go!" << std::endl;
    std::cout << std::endl;
}
