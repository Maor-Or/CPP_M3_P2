#pragma once

#include <iostream>

namespace ariel
{

    class Fraction
    {
    // private:
        int numerator, denominator;

        // my added private functions:
        void fractionReduction();

    public:
        // constructors:
        Fraction();
        Fraction(int numerator, int denominator);
        Fraction(float num);
        Fraction(const Fraction &other);
        Fraction(Fraction &&other) noexcept;

        // destructor:
        ~Fraction();

        // my added public functions:
        void setNumerator(int num);
        void setDenominator(int deno);
        void setValues(int num, int deno);

        // functions to implement:
        int getNumerator() const;
        int getDenominator() const;

        Fraction operator++(int); // postfix
        Fraction &operator++();   // prefix
        Fraction operator--(int);
        Fraction &operator--();

        Fraction &operator=(const Fraction &other);
        Fraction &operator=(Fraction &&other) noexcept;

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
        friend std::istream &operator>>(std::istream &input, Fraction &fraction);
        friend std::ostream &operator<<(std::ostream &output, const Fraction &fraction);
    };

} // namespace ariel
