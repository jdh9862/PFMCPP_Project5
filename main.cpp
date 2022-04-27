/*
 Project 5: Part 4 / 4
 video: Chapter 3 Part 7

 Create a branch named Part4
 
 Don't #include what you don't use
 
 1) Your task is to refactor your Chapter 3 Part 4 task into separate source and header files.
         Add files via the pane on the left.
 
 2) Put all of your declarations for each class in .h files
         One header file per class ( i.e. Raider.h for a class named "Raider" )
         Don't forget the '#pragma once'
 
 3) Put all of your implementations in .cpp files.
         one cpp file per class ( i.e. Raider.cpp for a class named "Raider" )
 
 4) Put all of your Wrapper classes in a single Wrappers.h file
         if you implemented your wrapper class functions in-class, you'll need to move them to Wrappers.cpp, which goes along with instruction 5): 
 
 5) NO IN-CLASS IMPLEMENTATION ALLOWED.
         the only exception is the existing Atomic.h and LeakedObjectDetector.h
        Chances are extremely high that you implemented your 
        wrapper class functions in-class, because that is what 
        everyone does after watching the video where I implemented 
        them in-class.
 
 6) for every .cpp file you have to make, insert it into the .replit file after 'main.cpp'.  Don't forget the spaces between file names.
 If you need help with this step, send me a DM.

 7) When you add the #include statements for your refactored source files into main.cpp: 
        '#include "Wrappers.h"' should be the first file that you include after LeakedObjectDetector.h
 
 8) Go through every cpp file and header file. check all function implementations for the following:
        Can this function argument be declared as 'const'? 
        Can this function be declared as 'const'?
        You learned about 'const' function arguments and 'const' functions in Project 5 Part 3
        As a refresher:
            If you aren't modifying the passed-in object inside the function, pass by 'const reference'.
            Marking a function parameter as 'const' means that you are promising that the parameter will not be modified.
            Additionally, you can mark class member functions as 'const'
            If you do this, you are promising that the member function will not modify any member variables.

        Mark every member function that is not modifying any member variables as 'const'
        Mark every function parameter that is not modified inside the function as 'const'
*/
#if false
//a function where the argument is passed by const-ref.
void Foo::someMemberFunction(const Axe& axe);

//a member function that is marked const, meaning it will not modify any member variables of the 'Axe' class.
void Axe::aConstMemberFunction() const { }
#endif
/*
 9) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Remember, your Chapter 3 Part 4 task worked when it was all in one file. so you shouldn't need to edit any of it.  
         just split it up into source files and provide the appropriate #include directives.
         tip: you cannot forward-declare nested types!  
         The file that a nested type is defined in MUST be included wherever that nested type is written.
 */

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

#include "Wrapper.h"
#include "PivotString.h"
#include "FancyPrinter.h"
#include "DividingStruct.h"

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
