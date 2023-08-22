
#include <cstdlib>
#include <iostream>
#include "BigInteger2.hpp"

using namespace std;

int main( )
{
    // Note the use of the C++ 2011 uniform initialization syntax.
    vtsu::BigInteger w{ "1234567890987654321012345678909876543210000000000" };
    vtsu::BigInteger x{ 9999 };
    vtsu::BigInteger y{ x };  // Uses the copy constructor.
    vtsu::BigInteger z;       // Uses the default constructor.

    z = x + y + w;            // Uses the copy assignment operator.

    cout << "The sum is " << z << "\n";

    // The destructor is implicitly invoked on 'w', 'x', 'y', and 'z' when they go out of scope.
    return EXIT_SUCCESS;
}
