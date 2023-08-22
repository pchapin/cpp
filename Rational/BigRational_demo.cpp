/*! \file   BigRational_demo.cpp
 *  \brief  A more interesting demonstration of the Rational template.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iostream>
#include "Rational.hpp"
#include "../BigInteger/BigInteger1.hpp"

using namespace std;

int main( )
{
    vtsu::Rational<vtsu::BigInteger> fraction_1{ 1, 2 };

    cout << "fraction_1 = " << fraction_1 << endl;
    
    return EXIT_SUCCESS;
}