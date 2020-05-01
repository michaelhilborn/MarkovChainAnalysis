#include "Fraction.h"

Fraction Fraction::Sum(Fraction otherFraction) {
    long n = numerator*otherFraction.denominator+otherFraction.numerator*denominator;
    long d = denominator*otherFraction.denominator;
    return Fraction(n/gcd(n,d),d/gcd(n,d));
}

Fraction Fraction::Difference(Fraction otherFraction){
    long n = numerator*otherFraction.denominator-otherFraction.numerator*denominator;
    long d = denominator*otherFraction.denominator;
    return Fraction(n/gcd(n,d),d/gcd(n,d));
}
Fraction Fraction::Product(Fraction otherFraction)
{
    long n = numerator*otherFraction.numerator;
    long d = denominator*otherFraction.denominator;
    return Fraction(n/gcd(n,d),d/gcd(n,d));
}
Fraction Fraction::Division(Fraction otherFraction)
{
    long n = numerator*otherFraction.denominator;
    long d = denominator*otherFraction.numerator;
    return Fraction(n/gcd(n,d),d/gcd(n,d));
}
long Fraction::gcd(long n, long d)
{
    long remainder;
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