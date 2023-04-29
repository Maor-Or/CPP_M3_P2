
#include <iostream>
#include <algorithm>
#include "Fraction.hpp"

using namespace std;
using namespace ariel;

// constructors:
Fraction::Fraction() : numerator(0), denominator(1) {}
Fraction::Fraction(int num, int denom)
{
    //checking for 0 in the denominator:
    if (denom == 0)
    {
        throw std::invalid_argument("cant divide by 0!");
    }
    
    //setting the values:
    numerator = num; denominator = denom;

    // keeping the denominator positive, switching the numerator 
    // from negative to positive and vice versa
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
Fraction::Fraction(Fraction &&other) noexcept
{
    numerator = other.numerator;
    denominator = other.denominator;
    other.numerator = 0;
    other.denominator = 1;
}

// destructor:
Fraction::~Fraction() {}

// my added functions:

// setters:
void Fraction::setNumerator(int num)
{
    numerator = num;
    fractionReduction();
}
void Fraction::setDenominator(int deno)
{
    if (deno == 0)
    {
        throw std::invalid_argument("cant divide by 0!");
    }
    denominator = deno;
    fractionReduction();
}
// i made this function incase both values are added one after the other.
// in that case, we only wish to reduce fraction once
void Fraction::setValues(int num, int deno)
{
    if (deno == 0)
    {
        throw std::invalid_argument("cant divide by 0!");
    }
    numerator = num;
    denominator = deno;
    fractionReduction();
}

// reducing the Fraction after some arithmetic action:
void Fraction::fractionReduction()
{
    // getting the gcd, using a built-in gcd function:
    int greatest_common_divider = __gcd(numerator, denominator);
    if (greatest_common_divider < 0)
        greatest_common_divider *= -1;

    // setting the new values:
    numerator = numerator / greatest_common_divider;
    denominator = denominator / greatest_common_divider;
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
Fraction Fraction::operator++(int)
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

// first return the original values and then update them:
Fraction Fraction::operator--(int)
{
    Fraction temp(*this);
    --(*this);
    return temp;
} // postfix

Fraction &Fraction::operator=(const Fraction &other)
{
    numerator = other.getNumerator();
    denominator = other.getDenominator();
    return *this;
}
Fraction &Fraction::operator=(Fraction &&other) noexcept
{
    if (this != &other)
    {
        numerator = other.numerator;
        denominator = other.denominator;
        other.numerator = 0;
        other.denominator = 1;
    }
    return *this;
}

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
bool operator>=(const Fraction &first, const Fraction &second) { return (first > second) || (first == second); }
bool operator<=(const Fraction &first, const Fraction &second) { return ((first < second) || (first == second)); }

istream &operator>>(std::istream &input, Fraction &fraction)
{
    int newNumerator, newDenominator;

    // get the values from the input stream:
    input >> newNumerator;
    input >> newDenominator;

    // Set the values to the Fraction object
    fraction.setValues(newNumerator, newDenominator);

    // Return the input stream object
    return input;
}
ostream &operator<<(std::ostream &output, const Fraction &fraction)
{
    // get the values from the Fraction object to the output stream:
    output << fraction.getNumerator();
    output << "/";
    output << fraction.getDenominator();

    // Return the output stream object
    return output;
}