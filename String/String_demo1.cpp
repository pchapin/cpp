
#include <iostream>
#include "String.hpp"

using namespace std;

int main( )
{
    vtc::String s1( "Hello" );  // Construct from a C-style string.
    vtc::String s2 = s1;        // Copy construct s2 from s1.

    s1[0] = 'x';

    cout << "s1 = " << s1 << "\n";
    cout << "s2 = " << s2 << "\n";

    s2 = s1;  // Assign s2 from s1.  (really: s2.operator=( s1 ))
    cout << "s2 = " << s2 << "\n";

    return 0;
}
