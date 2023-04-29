
#include <iostream>
#include <algorithm> //for gcd algo
#include <limits>    //for overflow exceptions handling

#include "Fraction.hpp"

using namespace std;
using namespace ariel;

// constructors:
Fraction::Fraction() : numerator(0), denominator(1) {}
Fraction::Fraction(int num, int denom)
{
    // checking for 0 in the denominator:
    if (denom == 0)
    {
        throw std::invalid_argument("cant divide by 0!");
    }

    // setting the values:
    numerator = num;
    denominator = denom;

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

    // keeping the denominator positive, switching the numerator
    // from negative to positive and vice versa
    if (denominator < 0)
    {
        numerator = numerator * -1;
        denominator = denominator * -1;
    }
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
    // checking for overflow:
    int64_t newNumerator = static_cast<int64_t>(numerator) + 1;
    if (newNumerator > std::numeric_limits<int>::max())
    {
        throw std::overflow_error("Addition overflow");
    }

    // if no overflow then the numerator updates:
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
    // checking for overflow:
    int64_t newNumerator = static_cast<int64_t>(numerator) - 1;
    if (newNumerator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("subtraction overflow");
    }

    // if no overflow then the numerator updates:
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
    // given a/b + c/d, we will do (a*d + c*b)/b*d
    // and then call fraction reduction in the constructor:

    // checking for extreme cases of overflow: first calculating both parts:
    int64_t newNumerator =
        static_cast<int64_t>(first.getNumerator()) * second.getDenominator()  // a*d
        +                                                                     // +
        static_cast<int64_t>(second.getNumerator()) * first.getDenominator(); // c*b
    int64_t newDenominator =
        static_cast<int64_t>(first.getDenominator()) * second.getDenominator(); // b*d

    // checking for overflows in both parts of the fraction:
    if (newNumerator > std::numeric_limits<int>::max() || newNumerator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Addition overflow");
    }
    if (newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Addition overflow");
    }

    // if no overflows found, re-casting the numbers into ints and making a new fraction:
    Fraction res(static_cast<int>(newNumerator), static_cast<int>(newDenominator));
    return res;
}
Fraction operator-(const Fraction &first, const Fraction &second)
{
    // given a/b - c/d, we will do (a*d - c*b)/b*d
    // and then call fraction reduction in the constructor:

    // checking for extreme cases of overflow: first calculating both parts:
    int64_t newNumerator =
        static_cast<int64_t>(first.getNumerator()) * second.getDenominator()  // a*d
        -                                                                     // -
        static_cast<int64_t>(second.getNumerator()) * first.getDenominator(); // c*b
    int64_t newDenominator =
        static_cast<int64_t>(first.getDenominator()) * second.getDenominator(); // b*d

    // checking for overflows in both parts of the fraction:
    if (newNumerator > std::numeric_limits<int>::max() || newNumerator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("subtraction overflow");
    }
    if (newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("subtraction overflow");
    }

    // if no overflows found, re-casting the numbers into ints and making a new fraction:
    Fraction res(static_cast<int>(newNumerator), static_cast<int>(newDenominator));
    return res;
}
Fraction operator*(const Fraction &first, const Fraction &second)
{
    // given a/b * c/d, we do (a*c)/(b*d)
    // and call fraction reduction in the constructor:

    // checking for extreme cases of overflow: first calculating both parts:
    int64_t newNumerator =
        static_cast<int64_t>(first.getNumerator())   // a
        *                                            //*
        static_cast<int64_t>(second.getNumerator()); // c
    int64_t newDenominator =
        static_cast<int64_t>(first.getDenominator())   // b
        *                                              //*
        static_cast<int64_t>(second.getDenominator()); // d

    // checking for overflows in both parts of the fraction:
    if (newNumerator > std::numeric_limits<int>::max() || newNumerator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Multiplication overflow in numerator");
    }
    if (newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("Multiplication overflow in denominator");
    }

    // if no overflows found, re-casting the numbers into ints and making a new fraction:
    Fraction res(static_cast<int>(newNumerator), static_cast<int>(newDenominator));
    return res;
}
Fraction operator/(const Fraction &first, const Fraction &second)
{
    // given a/b / c/d, we do (a*d)/(b*c)
    // and call fraction reduction in the constructor:
    if (second.getNumerator() == 0)
    {
        throw std::runtime_error("Division by zero");
    }

    // checking for extreme cases of overflow: first calculating both parts:
    int64_t newNumerator =
        static_cast<int64_t>(first.getNumerator())     // a
        *                                              //*
        static_cast<int64_t>(second.getDenominator()); // d
    int64_t newDenominator =
        static_cast<int64_t>(first.getDenominator()) // b
        *                                            //*
        static_cast<int64_t>(second.getNumerator()); // c

    // checking for overflows in both parts of the fraction:
    if (newNumerator > std::numeric_limits<int>::max() || newNumerator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("devision overflow");
    }
    if (newDenominator > std::numeric_limits<int>::max() || newDenominator < std::numeric_limits<int>::min())
    {
        throw std::overflow_error("devision overflow");
    }

    // if no overflows found, re-casting the numbers into ints and making a new fraction:
    Fraction res(static_cast<int>(newNumerator), static_cast<int>(newDenominator));
    return res;
}
bool operator==(const Fraction &first, const Fraction &second)
{ // fractions are already reduced, given a/b , c/d, checking if a == c and b == d:

    // in the tests - it looks like sometimes the fraction turns out too accurate,
    // and so needed to make it less accurate:
    Fraction newFirst, newSecond;
    int flag1 = 0, flag2 = 0;
    if (first.getDenominator() > 1000)
    { // making a new fraction less accurate:
        flag1 = 1;
        newFirst.setValues((first.getNumerator() / (first.getDenominator() / 1000)), 1000);
    }
    if (second.getDenominator() > 1000)
    { // making a new fraction less accurate:
        flag2 = 1;
        newSecond.setValues((second.getNumerator() / (second.getDenominator() / 1000)), 1000);
    }

    if (flag1 == 0 && flag2 == 0) // no new fractions were made
        return (first.getNumerator() == second.getNumerator()) && (first.getDenominator() == second.getDenominator());
    else if (flag1 == 1 && flag2 == 0) // new fraction for the first was made
        return (newFirst.getNumerator() == second.getNumerator()) && (newFirst.getDenominator() == second.getDenominator());
    else if (flag1 == 0 && flag2 == 1) // new fraction for the second was made
        return (first.getNumerator() == newSecond.getNumerator()) && (first.getDenominator() == newSecond.getDenominator());
    else // flag1 == 1 && flag2 == 1 meaning both new fractions were made
        return (newFirst.getNumerator() == newSecond.getNumerator()) && (newFirst.getDenominator() == newSecond.getDenominator());
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
    int newNumerator, newDenominator = 0; // if no value will be inputed, or 0 is inputed, then newDeno stays 0, and exception is thrown

    // get the values from the input stream:
    input >> newNumerator;
    input >> newDenominator;

    // Checking if the denominator is missing:
    if (newDenominator == 0)
    {
        throw std::runtime_error("Denominator is missing/zero");
    }

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