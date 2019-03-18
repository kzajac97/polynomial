#include "poly.hh"

int main(void)
{
    Polynomial a, b, c;
    a.MakePolynomial(2);
    b.MakePolynomial(1);
    c = a.DividePolynomial(b);
    c.PrintPolynomial();
}