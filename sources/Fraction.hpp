#pragma once

//TODO: delete if not needed:
//#include <string>

#include <iostream>

using namespace std;

class Fraction
{
// private:
    int numerator, denominator;

    //my added functions:
    void fractionReduction();

public:
    // constructors:
    Fraction();
    Fraction(int numerator, int denominator);
    Fraction(double num);
    Fraction(int num);
    Fraction(const Fraction &other);

    // functions to impliment:
    int getNumerator() const;
    int getDenominator() const;

    Fraction &operator++(int); // postfix
    Fraction &operator++();    // prefix
    Fraction &operator--(int);
    Fraction &operator--();

    // friend functions:
    friend Fraction operator+(const Fraction &first, const Fraction &second);
    friend Fraction operator-(const Fraction &first, const Fraction &second);
    friend Fraction operator*(const Fraction &first, const Fraction &second);
    friend Fraction operator/(const Fraction &first, const Fraction &second);
    friend bool operator==(const Fraction &first, const Fraction &second);
    friend bool operator!=(const Fraction &first, const Fraction &second);
    friend bool operator>(const Fraction &first, const Fraction &second);
    friend bool operator<(const Fraction &first, const Fraction &second);
    friend bool operator>=(const Fraction &first, const Fraction &second);
    friend bool operator<=(const Fraction &first, const Fraction &second);

    // IO:
    // friend ostream& operator>> (std::istream& output, const Fraction& fracNum);
    friend ostream &operator<<(std::ostream &output, const Fraction &fracNum);
};
namespace ariel
{
} // namespace ariel
