
#include <iostream>
#include "Fraction.hpp"

using namespace std;
using namespace ariel;

// constructors:
Fraction::Fraction() : numerator(0), denominator(1) {}
Fraction::Fraction(int num, int denom) : numerator(num), denominator(denom)
{
    // keeping the denominator positive, switching the numerator from negative to positive and vice versa
    if (denominator < 0)
    {
        numerator = numerator * -1;
        denominator = denominator * -1;
    }
    fractionReduction(); // reducing the fraction
}
Fraction::Fraction(double num) : numerator(num * 1000), denominator(1000) { fractionReduction(); }
Fraction::Fraction(int num) : numerator(num), denominator(1) {}
Fraction::Fraction(const Fraction &other) : numerator(other.getNumerator()), denominator(other.getDenominator())
{
    fractionReduction();
}

// my added functions:

// reducing the Fraction after some arithmetic action:
void Fraction::fractionReduction()
{
    // getting the gcd:
    int greatest_common_divider = gcdFind(numerator, denominator);

    // setting the new values:
    numerator = numerator / greatest_common_divider;
    denominator = denominator / greatest_common_divider;
}

// finding the gcd of the numerator and the denominator:
int gcdFind(int num1, int num2)
{
    int res = 1;

    // making both numbers positive:
    if (num1 < 0)
    {
        num1 = num1 * -1;
    }
    if (num2 < 0)
    {
        num2 = num2 * -1;
    }

    // picking the smaller number between the two
    if (num1 < num2)
    { // if num1 is smaller than num2 then
      // we first switch before checking all the numbers between 2 and the smaller number
        int temp = num2;
        num2 = num1;
        num1 = temp;
    }

    // finding the gcd (in the range between 2 to the smaller number, if none found then res is 1)
    for (int i = 2; i <= num2; ++i)
    {
        if (num1 % i == 0 && num2 % i == 0)
        {
            res = i;
        }
    }
    return res;
}

// functions to impliment:
int Fraction::getNumerator() const
{
    return numerator;
}

int Fraction::getDenominator() const
{
    return denominator;
}

Fraction &Fraction::operator++()
{
    numerator = numerator + denominator;
    fractionReduction();
    return *this;
} // prefix

// first return the original values and then update them:
Fraction &Fraction::operator++(int)
{
    Fraction temp(*this);
    ++(*this);
    return temp;
} // postfix

Fraction &Fraction::operator--()
{
    numerator = numerator - denominator;
    fractionReduction();
    return *this;
} // prefix

Fraction &Fraction::operator--(int)
{
    Fraction temp(*this);
    --(*this);
    return temp;
} // postfix

// friend functions:
Fraction operator+(const Fraction &first, const Fraction &second)
{
    // given a/b + c/d, we will do (a*d + c*b)/b*d and then call fraction reduction in the constructor:
    int leftNum = first.getNumerator() * second.getDenominator();          // a*d
    int rightNum = second.getNumerator() * first.getDenominator();         // c*b
    int newDenominator = first.getDenominator() * second.getDenominator(); // b*d

    Fraction res(leftNum + rightNum, newDenominator);
    return res;
}
Fraction operator-(const Fraction &first, const Fraction &second)
{
    // given a/b - c/d, we will do (a*d - c*b)/b*d and then call fraction reduction in the constructor:
    int leftNum = first.getNumerator() * second.getDenominator();          // a*d
    int rightNum = second.getNumerator() * first.getDenominator();         // c*b
    int newDenominator = first.getDenominator() * second.getDenominator(); // b*d

    Fraction res(leftNum - rightNum, newDenominator);
    return res;
}
Fraction operator*(const Fraction &first, const Fraction &second)
{
    // given a/b * c/d, we do (a*c)/(b*d) and call fraction reduction in the constructor:
    Fraction res(first.getNumerator() * second.getNumerator(), first.getDenominator() * second.getDenominator());
    return res;
}
Fraction operator/(const Fraction &first, const Fraction &second)
{
    // given a/b / c/d, we do (a*d)/(b*c) and call fraction reduction in the constructor:
    Fraction res(first.getNumerator() * second.getDenominator(), first.getDenominator() * second.getNumerator());
    return res;
}
bool operator==(const Fraction &first, const Fraction &second)
{ // fractions are already reduced, given a/b , c/d, checking if a == c and b == d:
    return (first.getNumerator() == second.getNumerator()) && (first.getDenominator() == second.getDenominator());
}
bool operator!=(const Fraction &first, const Fraction &second) { return !(first == second); }
bool operator>(const Fraction &first, const Fraction &second)
{ // given a/b ,c/d , checking if a*d > c*b:
    return (first.getNumerator() * second.getDenominator()) > (second.getNumerator() * first.getDenominator());
}
bool operator<(const Fraction &first, const Fraction &second)
{ // given a/b ,c/d , checking if a*d < c*b:
    return (first.getNumerator() * second.getDenominator()) < (second.getNumerator() * first.getDenominator());
}
bool operator>=(const Fraction &first, const Fraction &second) { return (first > second)||(first == second); }
bool operator<=(const Fraction &first, const Fraction &second) { (first < second)||(first == second); }

ostream &operator<<(std::ostream &output, const Fraction &fracNum) { return output; }