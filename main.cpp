/*
Project 5: Part 1 / 4
 video Chapter 2 - Part 12

 Create a branch named Part1

Purpose:  This project continues developing Project3.
       you will learn how to take code from existing projects and migrate only what you need to new projects
       you will learn how to write code that doesn't leak as well as how to refactor. 

NOTE: there are 2 sets of instructions:
       One for if you completed project 3
       One for if you skipped project 3.

 Destructors

===============================================================     
 If you completed Project 3:
 
 1) Copy 3 of your user-defined types (the ones with constructors and for()/while() loops from Project 3) here
    Choose the classes that contained nested classes.  Include the nested classes when you copy them over.

 2) move all of your implementations of all functions to OUTSIDE of the class.

 3) add destructors
        make the destructors do something like print out the name of the class.
===============================================================
If you skipped Project 3:
write 3 UDTs below that EACH have: 
        5 member variables
            the member variable names and types should be relevant to the work the UDT will perform.
            pick properties that can be represented with 'int float double bool char std::string'
        3 member functions with an arbitrary number of parameters
            give some of those parameters default values.
        constructors that initialize some of these member variables
            the remaining member variables should be initialized in-class
        for() or while() loops that modify member variables
 1) 2 of your 3 UDTs need to have a nested UDT.
    this nested UDT should fulfill the same requirements as above:
        5 member variables  
        3 member functions
        constructors and loops.
        
 2) Define your implementations of all functions OUTSIDE of the class. 
 NO IN-CLASS IMPLEMENTATION ALLOWED
 3) add destructors to all of your UDTs
        make the destructors do something like print out the name of the class.
===============================================================

 4) add 2 new UDTs that use only the types you copied above as member variables.

 5) add 2 member functions that use your member variables to each of these new UDTs

 6) Add constructors and destructors to these 2 new types that do stuff.  
        maybe print out the name of the class being destructed, or call a member function of one of the members.  be creative
 
 7) copy over your main() from the end of Project3 
        get it to compile with the types you copied over.
        remove any code in main() that uses types you didn't copy over.
 
 8) Instantiate your 2 UDT's from step 4) in the main() function at the bottom.
       call their member functions.
 
 9) After you finish, click the [run] button.  Clear up any errors or warnings as best you can.

 you can resolve any [-Wdeprecated] warnings by adding -Wno-deprecated to list of compiler arguments in the .replit file. all of the "-Wno" in that file are compiler arguments.
 You can resolve any [-Wpadded] warnings by adding -Wno-padded to the list of compiler arguments in the .replit file. all of the "-Wno" in that file are compiler arguments.

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


private:
    std::string mName;
    unsigned int mNumberOfLegs, mLastStep = 0, mFeetTraveled = 0;
    bool mCanRun, mIsRunning = false;
};

Animal::Animal(std::string name, unsigned int numberOfLegs, bool canRun)
    : mName(std::move(name)), mNumberOfLegs(numberOfLegs)
{
    if (canRun && numberOfLegs < 2) {
        std::cout << "Animals " << mName << " needs at least 2 legs to run" << std::endl;
        mCanRun = false;
    } else
    {
        mCanRun = canRun;
    }
}

Animal::~Animal()
{
    std::cout << "Animal " << mName << " traveled " << mFeetTraveled << " feet" << std::endl;
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
        std::cout << "Animal " << mName << " has no legs and rolls across the ground 1 foot" << std::endl;
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
    std::cout << "Animal " << mName << " traveled " << (mFeetTraveled - start) << " feet in " << numberOfSteps << " steps" << std::endl;
}

/*
 copied UDT 2:
 */
class PivotString
{
public:
    explicit PivotString(const std::string &string, bool reversePivot = false, bool reverseString = false, int pivotIndex = -1);

    ~PivotString();

    std::string getPart(bool first = true);

    std::string getFull();

    std::string reverse(std::string string);

private:
    int mPivotIndex, mCalls = 0;
    std::string mString;
    bool mReverseString, mReversePivot;
};

PivotString::PivotString(const std::string &string, bool reversePivot, bool reverseString , int pivotIndex)
    : mString(string), mReversePivot(reversePivot), mReverseString(reverseString)
{
    mPivotIndex = pivotIndex < 0 || pivotIndex > string.length() ? int(string.length() / 2) : pivotIndex;
}

PivotString::~PivotString()
{
    std::cout << "PivotString " << getFull() << " was called " << mCalls << " times" << std::endl;
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
        unsigned int i = string.length() - reversed.length() - 1;
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
        explicit MultiplierStruct(const SummingStruct& summingStruct);

        ~MultiplierStruct();

        void incrementInteger(unsigned int added);

        double multiplyAll() const;

        float multiplyFloats() const;

        int integer = 0;
        double firstDouble, secondDouble;
        float firstFloat, secondFloat;
    };
};

SummingStruct::SummingStruct(float first, float second) :
        firstDouble(static_cast<double>(first)),
        secondDouble(static_cast<double>(second)),
        firstFloat(first),
        secondFloat(second) { }

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
    return sumFloats() + firstDouble + secondDouble + integer;
}

float SummingStruct::sumFloats() const
{
    return firstFloat + secondFloat;
}

SummingStruct::MultiplierStruct::MultiplierStruct(const SummingStruct& summingStruct) :
        firstFloat(summingStruct.firstFloat),
        secondFloat(summingStruct.secondFloat),
        firstDouble(summingStruct.firstDouble),
        secondDouble(summingStruct.secondDouble) { }

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
    return multiplyFloats() * firstDouble * secondDouble * integer;
}

float SummingStruct::MultiplierStruct::multiplyFloats() const
{
    return firstFloat * secondFloat;
}


/*
 new UDT 4:
 with 2 member functions
 */

/*
 new UDT 5:
 with 2 member functions
 */

/*
 MAKE SURE YOU ARE NOT ON THE MASTER BRANCH

 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 If you didn't already: 
    Make a pull request after you make your first commit
    pin the pull request link and this repl.it link to our DM thread in a single message.

 send me a DM to review your pull request when the project is ready for review.

 Wait for my code review.
 */

int main()
{
    Animal pogoFrog {"Pogo Frog", 1, true};
    pogoFrog.travel(2);
    pogoFrog.startRunning();
    pogoFrog.travel(2);
    pogoFrog.stopRunning();
    pogoFrog.travel(1);

    Animal fishOutOfWater {"Fish", 0};
    fishOutOfWater.travel(2);
    fishOutOfWater.startRunning();
    fishOutOfWater.travel(2);
    fishOutOfWater.stopRunning();
    fishOutOfWater.travel(1);

    Animal dog {"Dog", 4, true};
    dog.travel(2);
    dog.startRunning();
    dog.travel(2);
    dog.stopRunning();
    dog.travel(1);
    std::cout << std::endl;

    PivotString simple {"simple"};
    PivotString reversed { "reversed", true, true};
    PivotString mangled {"mangled", false, true};
    PivotString first {"first", true, false, 1};
    PivotString last {"last", true, false, 4};
    std::cout << "PivotString simple = " << simple.getFull() << std::endl;
    std::cout << "PivotString reversed = " << reversed.getFull() << std::endl;
    std::cout << "PivotString mangled = " << mangled.getFull() << std::endl;
    std::cout << "PivotString first = " << first.getFull() << std::endl;
    std::cout << "PivotString last = " << last.getFull() << std::endl;
    std::cout << std::endl;

    SummingStruct summing {1.1f, 2.0f};
    summing.setInteger(-2);
    std::cout << "sumFloats = " << summing.sumFloats() << std::endl;
    std::cout << "sumAll = " << summing.sumAll() << std::endl;
    std::cout << std::endl;

    SummingStruct::MultiplierStruct multiplier {summing};
    multiplier.incrementInteger(3);
    std::cout << "multiplyFloats = " << multiplier.multiplyFloats() << std::endl;
    std::cout << "multiplyAll = " << multiplier.multiplyAll() << std::endl;
    std::cout << std::endl;

    std::cout << "good to go!" << std::endl;
    std::cout << std::endl;
}
