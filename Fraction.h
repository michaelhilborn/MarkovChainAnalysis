#include <iostream>
using namespace std;

//Coded by Sahat Yalkabov
//I received this code from her via stackoverflow

class Fraction
{
private:
    int numerator, denominator;
public:
    Fraction()
    {
        numerator = 1;
        denominator = 1;
    }
    Fraction(int n, int d)
    {
        numerator = n;
        if (d==0)
        {
            cout << "ERROR: ATTEMPTING TO DIVIDE BY ZERO" << endl;
            exit(0); // will terminate the program if division by 0 is attempted
        }
        else
            denominator = d;
    }
    /*In the following functions I am dividing both numerator and denominator by the gcd function.
    GCD function accepts both numerator and denominator values. If we had 2 fractions, 1/2 and 1/4
    and we passed it into the Sum, the result would be n=6 and d=8. These are the values that GCD
    function will accept, find greatest common divisor and return the integer value of 2. In my case
    am diving both numerator and denominator on the same line by the greatest common divisor. Although
    it probably would be more efficient to create a local int variable and store GCD value in it, but
    for such small program it shouldn't make any difference.*/
    Fraction Sum(Fraction otherFraction);
    Fraction Difference(Fraction otherFraction);
    Fraction Product(Fraction otherFraction);
    Fraction Division(Fraction otherFraction);

    // I got the GCD algorithm from the following source:
    // Source C#: http://www.ww.functionx.com/csharp2/examples/gcd.htm
    int gcd(int n, int d);

    void show(); // Display method
};
