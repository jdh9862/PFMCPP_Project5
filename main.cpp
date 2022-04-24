/*
Project 5: Part 2 / 4
 video: Chapter 3 Part 1

Create a branch named Part2

 The 'this' keyword
 
 The purpose of this project part is to show you how accessing member variables of objects INSIDE member functions is very similar to accessing member variables of objects OUTSIDE of member functions, via the 'this' keyword and arrow (->) operator and via the '.' operator.
 This project part will break the D.R.Y. rule, but that is fine for the purpose of this project part.
 
 Instructions:
 1) if you don't have any std::cout statements in main() that access member variables of your U.D.Ts
         write some.
    You can copy some from your Project3's main() if needed.

 2) Do the following for EVERY std::cout statement in main() that uses the UDT member variables and functions:
    a) write a member function that prints the same thing out, but uses the proper techniques inside the member functions to access the same member variables/functions.
    b) be explicit with your use of 'this->' in those member functions so we see how you're accessing/calling those member variables and functions *inside*
    c) call that member function AFTER your std::cout statement in main.
    NOTE: if your member functions being called in main() use std::cout statements, you don't need to create duplicates of these functions.  you only need to create member functions for the std::cout statements that exist in main().
        
 3) you should see 2 (almost) identical messages in the program output for each member function you add:
    one for the std::cout line, and one for the member function's output
 
 4) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.
 */

/*
 example:
 */
#include <iostream>
namespace Example
{
    //a User-Defined Type
    struct MyFoo
    {
        MyFoo();
        ~MyFoo();
        
        void printDetailedMemberInfo();
        
        int returnValue() { return 3; }
        float memberVariable = 3.14f;
    };

    MyFoo::MyFoo() { std::cout << "creating MyFoo" << std::endl; }
    MyFoo::~MyFoo() { std::cout << "destroying MyFoo" << std::endl; }
        
	// 2a) the member function whose function body is almost identical to the std::cout statement in main.
    //Remember to NAME FUNCTIONS WHAT THEY DO.
    void MyFoo::printDetailedMemberInfo() //function name contains a verb!!!
    { 
        // 2b) explicitly using 'this' inside this member function.
        std::cout << "MyFoo returnValue(): " << this->returnValue() << " and MyFoo memberVariable: " << this->memberVariable << std::endl; 
    }  
    
    int main()
    {
        //an instance of the User-Defined Type named mf
        MyFoo mf;
        
        // 1) a std::cout statement that uses mf's member variables
        std::cout << "mf returnValue(): " << mf.returnValue() << " and mf memberVariable: " << mf.memberVariable << std::endl; 
        
        // 2c) calling mf's member function.  the member function's body is almost identical to the cout statement above.
        mf.printDetailedMemberInfo();
        return 0;
    }
}

/*

 Ignore the Atomic.h and LeakedObjectDetector.h files for now.
 You will use those in Part 3 of this project.
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
        std::cout << "Animals " << name << " needs at least 2 legs to run"
                  << std::endl;
        canRun = false;
    }
    else
    {
        canRun = canRun_;
    }
}

Animal::~Animal()
{
    std::cout << "Animal " << name << " traveled " << feetTraveled << " feet"
              << std::endl;
}

void Animal::startRunning()
{
    if (canRun)
    {
        isRunning = true;
    }
    else
    {
        std::cout << "Animal " << name << " cannot run" << std::endl;
    }
}

void Animal::stopRunning()
{
    isRunning = false;
}

void Animal::travel(int numberOfSteps)
{
    if (numberOfLegs == 0)
    {
        std::cout << "Animal " << name
                  << " has no legs and rolls across the ground 1 foot"
                  << std::endl;
        ++feetTraveled;
        return;
    }
    unsigned int start = feetTraveled;
    for (int i = 0; i < numberOfSteps; ++i)
    {
        ++lastStep;
        if (lastStep >= numberOfLegs)
        {
            lastStep = 0;
            feetTraveled += isRunning ? 2 : 1;
        }
    }
    std::cout << "Animal " << name << " traveled " << (feetTraveled - start)
              << " feet in " << numberOfSteps << " steps" << std::endl;
}

Animal::Clock::Clock(bool is24Hour_) : is24Hour(is24Hour_)
{
    if (!is24Hour_)
    {
        isAM = new bool(true);
        hour = 12;
    }
}

Animal::Clock::~Clock()
{
    std::string suffix;
    if (!is24Hour)
    {
        suffix = isAM ? "AM" : "PM";
    }
    std::string mPrefix;
    if (minute < 10)
    {
        mPrefix = "0";
    }
    std::string sPrefix;
    if (second < 10)
    {
        sPrefix = "0";
    }
    std::cout << "The time is " << hour << ":" << mPrefix << minute << ":"
              << sPrefix << second << suffix << std::endl;
}

void Animal::Clock::incrementHour()
{
    ++hour;
    if (is24Hour)
    {
        if (hour == 24)
        {
            hour = 0;
        }
    }
    else
    {
        switch (hour)
        {
            case 12:
                isAM = !isAM;
                break;
            case 13:
                hour = 1;
                break;
        }
    }
}

void Animal::Clock::incrementMinute(bool silent)
{
    ++minute;
    if (minute == 60)
    {
        minute = 0;
        incrementHour();
        if (!silent)
        {
            int num = hour % 12;
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
    ++second;
    if (!silent)
    {
        std::cout << (second % 2 ? "tick" : "tock") << std::endl;
    }
    if (second == 60)
    {
        second = 0;
        incrementMinute(silent);
    }
}

void Animal::Clock::wind(
        unsigned int hours,
        unsigned int minutes,
        unsigned int seconds)
{
    for (unsigned int s = 0; s < seconds; ++s)
    {
        incrementSecond(true);
    }
    for (unsigned int m = 0; m < minutes; ++m)
    {
        incrementMinute(true);
    }
    for (unsigned int h = 0; h < hours; ++h)
    {
        incrementHour();
    }
}

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
    pivotIndex = pivotIndex_ > string_.length()
                  ? string_.length() / 2
                  : pivotIndex_;
}

PivotString::~PivotString()
{
    std::cout << "PivotString " << getFull() << " was called " << calls
              << " times" << std::endl;
}

std::string PivotString::getPart(bool first)
{
    ++calls;
    if (first)
    {
        return string.substr(0, pivotIndex);
    }
    else FIXME: see message in Slack
    {
        return string.substr(pivotIndex, string.length() - pivotIndex);
    }
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
    integer = 0;
    while (integer < abs(newValue))
    {
        ++integer;
    }
}

double SummingStruct::sumAll() const
{
    return double(sumFloats()) + firstDouble + secondDouble + integer;
}

float SummingStruct::sumFloats() const
{
    return firstFloat + secondFloat;
}

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
        ++integer;
    }
}

double SummingStruct::MultiplierStruct::multiplyAll() const
{
    return double(multiplyFloats()) * firstDouble * secondDouble * integer;
}

float SummingStruct::MultiplierStruct::multiplyFloats() const
{
    return firstFloat * secondFloat;
}

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
              << p1.calls + p2.calls << " times" << std::endl;
}

void FancyPrinter::print() const
{
    std::string s1, s2, s3, s4;
    getParts(p1, s1, s3);
    getParts(p2, s2, s4);
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
    return multiplier.multiplyAll() / summing.sumAll();
}

void DividingStruct::modifyIntegers(unsigned int i)
{
    summing.setInteger(int(i));
    multiplier.incrementInteger(i);
}

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
    Animal pogoFrog{"Pogo Frog", 1, true};
    pogoFrog.travel(2);
    pogoFrog.startRunning();
    pogoFrog.travel(2);
    pogoFrog.stopRunning();
    pogoFrog.travel(1);

    Animal fishOutOfWater{"Fish", 0};
    fishOutOfWater.travel(2);
    fishOutOfWater.startRunning();
    fishOutOfWater.travel(2);
    fishOutOfWater.stopRunning();
    fishOutOfWater.travel(1);

    Animal dog{"Dog", 4, true};
    dog.travel(2);
    dog.startRunning();
    dog.travel(2);
    dog.stopRunning();
    dog.travel(1);
    std::cout << std::endl;

    Animal::Clock clock1{true};
    clock1.wind(23, 59, 59);
    clock1.incrementSecond();
    clock1.incrementSecond();
    std::cout << std::endl;

    Animal::Clock clock2{false};
    clock2.wind(12, 59, 58);
    clock2.incrementSecond();
    clock2.incrementSecond();
    std::cout << std::endl;

    PivotString simple{"simple"};
    PivotString reversed{"reversed", true, true};
    PivotString mangled{"mangled", false, true, 100};
    PivotString first{"first", true, false, 1};
    PivotString last{"last", true, false, 4};
    std::cout << "PivotString simple = " << simple.getFull() << std::endl;
    std::cout << "PivotString reversed = " << reversed.getFull() << std::endl;
    std::cout << "PivotString mangled = " << mangled.getFull() << std::endl;
    std::cout << "PivotString first = " << first.getFull() << std::endl;
    std::cout << "PivotString last = " << last.getFull() << std::endl;
    std::cout << std::endl;

    SummingStruct summing{1.1f, 2.0f};
    summing.setInteger(-2);
    std::cout << "sumFloats = " << summing.sumFloats() << std::endl;
    std::cout << "sumAll = " << summing.sumAll() << std::endl;
    std::cout << std::endl;

    SummingStruct::MultiplierStruct multiplier{summing};
    multiplier.incrementInteger(3);
    std::cout << "multiplyFloats = " << multiplier.multiplyFloats()
              << std::endl;
    std::cout << "multiplyAll = " << multiplier.multiplyAll() << std::endl;
    std::cout << std::endl;

    FancyPrinter p{simple, mangled};
    p.print();
    std::cout << std::endl;

    DividingStruct divider{summing};
    // Result will be zero because the multiplier's integer has not been
    // incremented
    std::cout << "divide before = " << divider.divide() << std::endl;
    divider.modifyIntegers(1);
    std::cout << "divide after = " << divider.divide() << std::endl;
    std::cout << std::endl;

    std::cout << "good to go!" << std::endl;
    std::cout << std::endl;
}
