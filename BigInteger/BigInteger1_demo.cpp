
#include <cstdlib>
#include <iostream>
#include "BigInteger1.hpp"

using namespace std;

int main( )
{
    vtsu::BigInteger w{ "1234567890987654321012345678909876543210000000000" };
    vtsu::BigInteger x{ 9999 };
    vtsu::BigInteger y{ x };  // Uses the auto-generated copy constructor.
    vtsu::BigInteger z;       // Uses the default constructor.

    z = w + x + y;  // Uses generated assignment operator.

    cout << "The sum is " << z << endl;
    return EXIT_SUCCESS;
}
