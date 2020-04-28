#include "Fraction.h"

Fraction Fraction::Sum(Fraction otherFraction) {
    int n = numerator*otherFraction.denominator+otherFraction.numerator*denominator;
    int d = denominator*otherFraction.denominator;
    return Fraction(n/gcd(n,d),d/gcd(n,d));
}

Fraction Fraction::Difference(Fraction otherFraction){
    int n = numerator*otherFraction.denominator-otherFraction.numerator*denominator;
    int d = denominator*otherFraction.denominator;
    return Fraction(n/gcd(n,d),d/gcd(n,d));
}
Fraction Fraction::Product(Fraction otherFraction)
{
    int n = numerator*otherFraction.numerator;
    int d = denominator*otherFraction.denominator;
    return Fraction(n/gcd(n,d),d/gcd(n,d));
}
Fraction Fraction::Division(Fraction otherFraction)
{
    int n = numerator*otherFraction.denominator;
    int d = denominator*otherFraction.numerator;
    return Fraction(n/gcd(n,d),d/gcd(n,d));
}
int Fraction::gcd(int n, int d)
{
    int remainder;
    while (d != 0)
    {
        remainder = n % d;
        n = d;
        d = remainder;
    }
    return n;
}

void Fraction::show() // Display method
{
    if (denominator == 1) // e.g. fraction 2/1 will display simply as 2
        cout << numerator;
    else
        cout << numerator << "/" << denominator;
}