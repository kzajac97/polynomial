#pragma once

#include <iostream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <cmath>

using coeff_t = double;

class Polynomial 
{
    /*
    structure holding polynomials terms
    it contains terms coefficient and 
    exponent coresponding to it
    */
    struct term
    {
        int exponent;
        coeff_t coeff;

        term() = default;
        term(int initExponent, coeff_t initCoeff) : exponent(initExponent), coeff(initCoeff) {};
    };
    
    std::vector<term> terms;
    
    public:

    Polynomial() = default;
    ~Polynomial(void) { this->terms.clear(); }

    const void MakePolynomial(int degree);
    const void BuildPolynomial(std::vector<coeff_t> coeffs);
    const void PrintPolynomial(void) { print(); }
    const Polynomial AddPolynomial(Polynomial arg) { return add(arg); }
    const Polynomial SubtractPolynomial(Polynomial arg) { return subtract(arg); }
    const Polynomial MulitplyPolynomial(Polynomial arg) { return multiply(arg); }
    const Polynomial DividePolynomial(Polynomial arg) { return divide(arg); }
    const Polynomial RaisePolynomial(int power) { return raise(power); }
    
    const Polynomial operator + (Polynomial arg) { return add(arg); }
    const Polynomial operator - (Polynomial arg) { return subtract(arg); }
    const Polynomial operator * (Polynomial arg) { return multiply(arg); }
    const Polynomial operator / (Polynomial arg) { return divide(arg); }
    const Polynomial operator ^ (int power) { return raise(power); }
    
    private:

    //pretty printing method
    const void print();

    /*
    adds to polynomials and returns the output
    firstly the method adds coefficients with
    coresponding exponents and than fills the 
    result polynomial with elements which have 
    exponents which are not in a result but are
    in one of the input polynomials
    */
    const Polynomial add(Polynomial arg);
    
    /*
    method subtracts polynomials by reversing
    all the signs of coefficients in the second
    polynomial and than adds them
    */
    const Polynomial subtract(Polynomial arg) { return add(arg.reverse_signs()); }

    /*
    muliplies two polynomials element by element
    and than simplifies the result summing 
    elements with equal exponents
    */
    const Polynomial multiply(Polynomial arg);
    
    /*
    implementation of long polynomial division 
    algorithm returns correct value only 
    if given polynomials are divisable 
    */
    const Polynomial divide(Polynomial arg);
    
    /*
    raises polynomial to given power 
    multipling it by itself n times
    */
    const Polynomial raise(int power);
    
    //utility methods
    
    /*
    checks if two polynomials have elemnts with equal exponents
    returns true if they do and false if not
    */
    const bool find_element(term arg);

    /*
    sorts polynomial in decreasing order of
    exponents using insertion sort
    */
    void sort(std::vector<term> &array, int first, int last);
    //method to call insertion sort
    void sort_poly(void) { sort(terms,0, terms.size()-1); }
    //reverses signs in a polynomial
    Polynomial reverse_signs(void);
    
    /*
    adds up coefficients with equal exponents
    in a single polynomial
    */
    void simplify_poly(void); 
    //pops elements with zero coefficients
    void reduce_poly(void);
    //pretty prints coefficients 
    const void print_coeff(term arg);
    //returns degree of given polynomial
    const int get_degree(void) { return terms[0].exponent; }
    //divides two single terms of polynomial
    const term divide_element(term dividen, term divisor);
};