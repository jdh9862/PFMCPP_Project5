/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3.
	   you will learn how to take code from existing projects and migrate only
what you need to new projects you will learn how to write code that doesn't leak as well as how to refactor.

NOTE: there are 2 sets of instructions:
	   One for if you completed project 3
	   One for if you skipped project 3.

 Destructors

===============================================================
 If you completed Project 3:

 1) Copy 3 of your user-defined types (the ones with constructors and
for()/while() loops from Project 3) here Choose the classes that contained
nested classes.  Include the nested classes when you copy them over.

 2) move all of your implementations of all functions to OUTSIDE of the class.

 3) add destructors
		make the destructors do something like print out the name of the class.
===============================================================
If you skipped Project 3:
write 3 UDTs below that EACH have:
		5 member variables
			the member variable names and types should be relevant to the work
the UDT will perform. pick properties that can be represented with 'int float
double bool char std::string' 3 member functions with an arbitrary number of
parameters give some of those parameters default values. constructors that
initialize some of these member variables the remaining member variables should
be initialized in-class for() or while() loops that modify member variables 1) 2
of your 3 UDTs need to have a nested UDT. this nested UDT should fulfill the
same requirements as above: 5 member variables 3 member functions constructors
and loops.

 2) Define your implementations of all functions OUTSIDE of the class.
 NO IN-CLASS IMPLEMENTATION ALLOWED
 3) add destructors to all of your UDTs
		make the destructors do something like print out the name of the class.
===============================================================

 4) add 2 new UDTs that use only the types you copied above as member variables.

 5) add 2 member functions that use your member variables to each of these new
UDTs

 6) Add constructors and destructors to these 2 new types that do stuff.
		maybe print out the name of the class being destructed, or call a member
function of one of the members.  be creative

 7) copy over your main() from the end of Project3
		get it to compile with the types you copied over.
		remove any code in main() that uses types you didn't copy over.

 8) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
	   call their member functions.

 9) After you finish, click the [run] button.  Clear up any errors or warnings
as best you can.

 you can resolve any [-Wdeprecated] warnings by adding -Wno-deprecated to list
of compiler arguments in the .replit file. all of the "-Wno" in that file are
compiler arguments. You can resolve any [-Wpadded] warnings by adding
-Wno-padded to the list of compiler arguments in the .replit file. all of the
"-Wno" in that file are compiler arguments.

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
    Animal(std::string name, unsigned int numberOfLegs, bool canRun = false);

    ~Animal();

    void startRunning();

    void stopRunning();

    void travel(int numberOfSteps);

    class Clock
    {
    public:
        explicit Clock(bool is24Hour);

        ~Clock();

        void incrementHour();

        void incrementMinute(bool silent = false);

        void incrementSecond(bool silent = false);

        void
        wind(unsigned int hours, unsigned int minutes, unsigned int seconds);

    private:
        bool mIs24Hour;
        bool *mIsAM = nullptr;
        int mHour = 0, mMinute = 0, mSecond = 0;
    };

private:
    std::string mName;
    unsigned int mNumberOfLegs, mLastStep = 0, mFeetTraveled = 0;
    bool mCanRun, mIsRunning = false;
};

Animal::Animal(std::string name, unsigned int numberOfLegs, bool canRun)
        : mName(std::move(name)), mNumberOfLegs(numberOfLegs)
{
    if (canRun && numberOfLegs < 2)
    {
        std::cout << "Animals " << mName << " needs at least 2 legs to run"
                  << std::endl;
        mCanRun = false;
    } else
    {
        mCanRun = canRun;
    }
}

Animal::~Animal()
{
    std::cout << "Animal " << mName << " traveled " << mFeetTraveled << " feet"
              << std::endl;
}

void Animal::startRunning()
{
    if (mCanRun)
    {
        mIsRunning = true;
    } else
    {
        std::cout << "Animal " << mName << " cannot run" << std::endl;
    }
}

void Animal::stopRunning()
{
    mIsRunning = false;
}

void Animal::travel(int numberOfSteps)
{
    if (mNumberOfLegs == 0)
    {
        std::cout << "Animal " << mName
                  << " has no legs and rolls across the ground 1 foot"
                  << std::endl;
        mFeetTraveled++;
        return;
    }
    unsigned int start = mFeetTraveled;
    for (int i = 0; i < numberOfSteps; i++)
    {
        mLastStep++;
        if (mLastStep >= mNumberOfLegs)
        {
            mLastStep = 0;
            mFeetTraveled += mIsRunning ? 2 : 1;
        }
    }
    std::cout << "Animal " << mName << " traveled " << (mFeetTraveled - start)
              << " feet in " << numberOfSteps << " steps" << std::endl;
}

Animal::Clock::Clock(bool is24Hour) : mIs24Hour(is24Hour)
{
    if (!is24Hour)
    {
        mIsAM = new bool(true);
        mHour = 12;
    }
}

Animal::Clock::~Clock()
{
    std::string suffix;
    if (!mIs24Hour && mIsAM != nullptr)
    {
        suffix = *mIsAM ? "AM" : "PM";
        delete mIsAM;
    }
    std::string mPrefix;
    if (mMinute < 10)
    {
        mPrefix = "0";
    }
    std::string sPrefix;
    if (mSecond < 10)
    {
        sPrefix = "0";
    }
    std::cout << "The time is " << mHour << ":" << mPrefix << mMinute << ":"
              << sPrefix << mSecond << suffix << std::endl;
}

void Animal::Clock::incrementHour()
{
    mHour++;
    if (mIs24Hour)
    {
        if (mHour == 24)
        {
            mHour = 0;
        }
    } else
    {
        switch (mHour)
        {
            case 12:
                if (mIsAM != nullptr)
                {
                    *mIsAM = !*mIsAM;
                }
                break;
            case 13:
                mHour = 1;
                break;
        }
    }
}

void Animal::Clock::incrementMinute(bool silent)
{
    mMinute++;
    if (mMinute == 60)
    {
        mMinute = 0;
        incrementHour();
        if (!silent)
        {
            int num = mHour % 12;
            if (num == 0)
            {
                num = 12;
            }
            for (int i = 0; i < num; i++)
            {
                std::cout << "Clang" << std::endl;
            }
        }
    }
}

void Animal::Clock::incrementSecond(bool silent)
{
    mSecond++;
    if (!silent)
    {
        std::cout << (mSecond % 2 ? "tick" : "tock") << std::endl;
    }
    if (mSecond == 60)
    {
        mSecond = 0;
        incrementMinute(silent);
    }
}

void Animal::Clock::wind(
        unsigned int hours,
        unsigned int minutes,
        unsigned int seconds)
{
    for (unsigned int s = 0; s < seconds; s++)
    {
        incrementSecond(true);
    }
    for (unsigned int m = 0; m < minutes; m++)
    {
        incrementMinute(true);
    }
    for (unsigned int h = 0; h < hours; h++)
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
            const std::string &string,
            bool reversePivot = false,
            bool reverseString = false,
            unsigned long pivotIndex = 0);

    ~PivotString();

    std::string getPart(bool first = true);

    std::string getFull();

    std::string reverse(std::string string);

    int mCalls = 0;
    unsigned long mPivotIndex;
    std::string mString;
    bool mReversePivot, mReverseString;
};

PivotString::PivotString(
        const std::string &string,
        bool reversePivot,
        bool reverseString,
        unsigned long pivotIndex)
        : mString(string),
          mReversePivot(reversePivot),
          mReverseString(reverseString)
{
    mPivotIndex = pivotIndex > string.length()
                  ? string.length() / 2
                  : pivotIndex;
}

PivotString::~PivotString()
{
    std::cout << "PivotString " << getFull() << " was called " << mCalls
              << " times" << std::endl;
}

std::string PivotString::getPart(bool first)
{
    mCalls++;
    if (first)
    {
        return mString.substr(0, mPivotIndex);
    } else
    {
        return mString.substr(mPivotIndex, mString.length() - mPivotIndex);
    }
}

std::string PivotString::getFull()
{
    mCalls++;
    std::string first = getPart();
    std::string second = getPart(false);
    if (mReverseString)
    {
        first = reverse(first);
        second = reverse(second);
    }
    return mReversePivot ? second + first : first + second;
}

std::string PivotString::reverse(std::string string)
{
    mCalls++;
    std::string reversed;
    while (reversed.length() < string.length())
    {
        unsigned long i = string.length() - reversed.length() - 1;
        reversed.push_back(string[i]);
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
        integer++;
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
        added--;
        integer++;
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
              << p1.mCalls + p2.mCalls << " times" << std::endl;
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
    if (p.mReversePivot)
    {
        s1 = p.getPart(false);
        s2 = p.getPart();
    } else
    {
        s1 = p.getPart();
        s2 = p.getPart(false);
    }
    if (p.mReverseString)
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

    auto *clock1 = new Animal::Clock(true);
    clock1->wind(23, 59, 59);
    clock1->incrementSecond();
    clock1->incrementSecond();
    delete clock1;
    std::cout << std::endl;

    auto *clock2 = new Animal::Clock(false);
    clock2->wind(12, 59, 58);
    clock2->incrementSecond();
    clock2->incrementSecond();
    delete clock2;
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
