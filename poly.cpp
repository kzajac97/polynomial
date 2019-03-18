#include "poly.hh"

//Public methods
const void Polynomial::MakePolynomial(int degree)
{
    term initTerm;

    for(int i=0; i <= degree; i++)
    {
        std::cin >> initTerm.coeff;
        if(initTerm.coeff != 0.0f)
        {
            initTerm.exponent = degree - i;
            terms.push_back(initTerm);
        }
    }
}

const void Polynomial::BuildPolynomial(std::vector<coeff_t> coeffs)
{
    term initTerm;

    for(unsigned i=0; i < coeffs.size(); i++)
    {
        if(coeffs[i] != 0.0f)
        {
            initTerm.exponent = coeffs.size() - i;
            terms.push_back(initTerm);
        }
    }
}

//private methods

const void Polynomial::print()
{
    if(terms.empty())
        { std::cout << "0"; }

    sort_poly();

    for(const auto &term : terms)
    {
        if(term.exponent == 0)            
            { print_coeff(term); }
        else if(term.exponent == 1)
            { print_coeff(term); std::cout << "x"; }
        else
            { print_coeff(term); std::cout << "x^" << term.exponent; }          
    }

    std::cout << "\n";
}

const Polynomial Polynomial::add(Polynomial arg)
{
    Polynomial result;
    term resultTerm;
    
    for(unsigned i=0; i < terms.size(); i++)
    {
        for(unsigned j=0; j < arg.terms.size(); j++)
        {
            if(terms[i].exponent == arg.terms[j].exponent)
            {
                resultTerm.coeff = terms[i].coeff + arg.terms[j].coeff;
                resultTerm.exponent = terms[i].exponent;                
                result.terms.push_back(resultTerm);
            }
        }
    }

    //copy remaining elements from first argument
    for(const auto &element : terms)
    {
        if(!result.find_element(element))
        {
            resultTerm.coeff = element.coeff;
            resultTerm.exponent = element.exponent;                
            result.terms.push_back(resultTerm);
        }
    }

    //copy remaining elements from second argument
    for(const auto &element : arg.terms)
    {
        if(!result.find_element(element))
        {
            resultTerm.coeff = element.coeff;
            resultTerm.exponent = element.exponent;                
            result.terms.push_back(resultTerm);
        }
    }

    result.reduce_poly();

    return result;
}

const Polynomial Polynomial::multiply(Polynomial arg)
{
    Polynomial result;
    term resultTerm;

    for(unsigned i=0; i < terms.size(); i++)
    {
        for(unsigned j=0; j < arg.terms.size(); j++)
        {
            resultTerm.coeff = terms[i].coeff * arg.terms[j].coeff;
            resultTerm.exponent = terms[i].exponent + arg.terms[j].exponent;
            result.terms.push_back(resultTerm);
        }
    }

    result.simplify_poly();
    result.reduce_poly();

    return result;
}

const Polynomial Polynomial::divide(Polynomial arg)
{
    int degree = get_degree();
    Polynomial result;
    Polynomial currentPoly = *(this);
    term resultTerm;

    for(int i=1; i <= degree; i++)
    {
        resultTerm = divide_element(currentPoly.terms[0],arg.terms[0]);
        result.terms.push_back(resultTerm);       
        currentPoly = (*this) - (result * arg);       
    }

    return result;
}

const Polynomial Polynomial::raise(int power)
{
    Polynomial result = (*this);

    for(int i=1; i < power; i++)
        { result = result.multiply(*this); }
    
    return result;
}

//utility methods

const bool Polynomial::find_element(term arg)
{
    for(const auto &term : terms)
    {
        if(term.exponent == arg.exponent)
            { return true; }
    }

    return false;
}

void Polynomial::sort(std::vector<term> &array, int first, int last)
{
    term tmp;
    int j;
    //first element is already sorted
    for(int i=first; i<(last-first); ++i)
    {
        tmp = array[i];
        j = i;
        //while element's exponent is greater than current value
        while(j>0 && array[j-1].exponent < tmp.exponent)
        {
            //insert element before current value
            array[j] = array[j-1];
            j--;
        }
        //if no greater elements insert after current value
        array[j] = tmp;
    }
}

Polynomial Polynomial::reverse_signs(void)
{
    Polynomial result;
    result.terms = terms;

    for(unsigned i=0; i < terms.size(); i++)
        { result.terms[i].coeff = -terms[i].coeff; }

    return result;
}

const Polynomial::term Polynomial::divide_element(term divident, term divisor)
{
    term result;

    result.coeff = divident.coeff/divisor.coeff;
    result.exponent = divident.exponent - divisor.exponent;

    return result;
}

void Polynomial::reduce_poly(void)
{
    for(unsigned i=0; i < terms.size(); i++)
    {
        if(terms[i].coeff == 0)
            { terms.erase(terms.begin() + i); } 
    }
}

void Polynomial::simplify_poly(void)
{
    term resultTerm;
    std::vector<term> result;
    int degree = get_degree();

    for(int i=0; i <= degree; i++)
    {
        resultTerm.exponent = degree - i;
        resultTerm.coeff = 0;

        for(const auto &term : terms)
        {
            if(term.exponent == degree - i)
                { resultTerm.coeff += term.coeff; }
        }

        result.push_back(resultTerm);
    }

    terms.erase(terms.begin(),terms.end());
    terms = result;
}

const void Polynomial::print_coeff(term arg)
{
    if(arg.coeff > 0)
        { std::cout << " + "; }
    else if(arg.coeff < 0) 
        { std::cout << " - "; }
    
    if(arg.coeff == 1 && arg.exponent == 0)
        { std::cout << "1"; }

    if(arg.coeff != 1)
        { std::cout << std::abs(arg.coeff); }
}