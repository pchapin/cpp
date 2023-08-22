/*! \file   Rational_demo.cpp
 *  \brief  A simple demonstration of the Rational template.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iostream>
#include "Rational.hpp"

using namespace std;

int main( )
{
    // Because Rationals are pseudo-immutable, the only effect of adding `const` to a
    // declaration is to prevent that rational value from being overwritten during in input
    // operation.
    vtsu::Rational<unsigned> fraction_1{ 1, 2 };
    vtsu::Rational<unsigned> fraction_2{ 5 };
    const vtsu::Rational<unsigned> fraction_3{ 1, 3 };  // Cannot be overwritten from an input stream.
    vtsu::Rational<unsigned> fraction_4 = fraction_1;   // Copy construction is permitted.
 
    cout << "fraction_1 = " << fraction_1 << endl;
    cout << "fraction_2 = " << fraction_2 << endl;
    cout << "fraction_3 = " << fraction_3 << endl;
    cout << "fraction_4 = " << fraction_4 << endl;

    // fraction_4 = fraction_1;  // Assignment is not permitted.

    // However, extraction from an input stream *is* allowed (if the object isn't const).
    cout << "Enter a new value for fraction_4: ";
    cin  >> fraction_4;
    cout << "You entered: " << fraction_4 << endl;

    // A relatively simple computation. Just add them together.
    vtsu::Rational<unsigned> result_1 = fraction_1 + fraction_2 + fraction_3 + fraction_4;

    // A more elaborate computation.
    vtsu::Rational<unsigned> result_2 =
        ( fraction_4 * (fraction_1 + fraction_2) ) / (fraction_1 - fraction_3);

    cout << '\n';
    cout << "result_1 = " << result_1 << endl;
    cout << "result_2 = " << result_2 << endl;

    return EXIT_SUCCESS;
}
