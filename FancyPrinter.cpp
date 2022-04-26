#include "FancyPrinter.h"

FancyPrinter::FancyPrinter(const PivotString& pivot1, const PivotString& pivot2)
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

void FancyPrinter::getParts(PivotString p, std::string& s1, std::string& s2)
{
    if (p.reversePivot)
    {
        s1 = p.getPart(false);
        s2 = p.getPart();
    } else
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
