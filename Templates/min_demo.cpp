
#include <cstdlib>
#include <iostream>
#include <string>
#include "min.hpp"

using namespace std;

int main( )
{
    int a, b;
    cout << "Enter 'a' and 'b': ";
    cin >> a;
    cin >> b;

    // When the template instance min taking two integers is used, the compiler generates it.
    // The body of the template is compiled for the T=int and the operations in the template are
    // checked for validity. The temlate is not semantically checked when it is first seen (when
    // the header file is processed).
    //
    cout << "The minimum is " << vtc::min(a, b) << "\n";

    double x, y;
    cout << "Enter 'x' and 'y': ";
    cin >> x;
    cin >> y;

    // Here another instance of min (the one taking two doubles) is used. Note that the
    // programmer does not need to explicity create a template instance (but C++ does allow that
    // if desired). Instead the compiler deduces the type arguments (T=double in this case) from
    // the arguments provided in the call (two doubles).
    //
    cout << "The minimum is " << vtc::min(x, y) << "\n";

    string s1, s2;
    cout << "Enter 's1' and 's2': ";
    cin >> s1;
    cin >> s2;

    // This instance of min (T=std::string) is okay beause std::string has the necessary '<'
    // operator required by the template. TO check this the compiler needs to see the template
    // body. Thus templats are always defined in header files, even if they are not inline
    // expanded.
    //
    cout << "The minimum is " << vtc::min(s1, s2) << "\n";

    return EXIT_SUCCESS;
}
