
#include <chrono>
#include <cstdlib>
#include <iostream>

using namespace std;

// The purpose of this file is to experiment with C++ 2020's chrono library.

int main( )
{
    using namespace chrono_literals;

    auto d1 = 2023y / 5 / 5;
    auto d2 = 5d / 5 / 2023;
    auto d3 = chrono::May / 5 / 2023;

    // My understanding is that the C++ 2020 standard requires an operator<<( ) for the
    // type chrono::year_month_day. However, the version of GCC that I am using does not
    // have this operator. Therefore, I am commenting out the following lines of code.
    //
    // cout << "d1 = " << d1 << endl;
    // cout << "d2 = " << d2 << endl;
    // cout << "d3 = " << d3 << endl;
    return EXIT_SUCCESS;
}