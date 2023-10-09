
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include "min.hpp"

using namespace std;

int main( )
{
    cout << fixed;
    cout << setprecision( 4 );
    
    int a, b;
    cout << "Enter ints 'a' and 'b': ";
    cin >> a;
    cin >> b;

    // When the template specialization `min` taking two integers is used, the compiler
    // generates it. The body of the template is compiled for the T=int and the operations in
    // the template are checked for validity. The temlate is not semantically checked when it is
    // first seen (when the header file is processed).
    //
    cout << "The minimum is " << vtsu::min( a, b ) << endl;

    double x, y;
    cout << "Enter doubles 'x' and 'y': ";
    cin >> x;
    cin >> y;

    // Here another specialization of `min` (the one taking two doubles) is used. Note that the
    // programmer does not need to explicity create a template specialization (but C++ does
    // allow that if desired). Instead the compiler deduces the type arguments (T=double in this
    // case) from the arguments provided in the call (two doubles).
    //
    cout << "The minimum is " << vtsu::min( x, y ) << endl;

    string s1, s2;
    cout << "Enter strings 's1' and 's2': ";
    cin >> s1;
    cin >> s2;

    // This specialization of `min` (T=std::string) is okay beause std::string has the necessary
    // '<' operator required by the template. To check this the compiler needs to see the
    // template body. Thus templats are always defined in header files, even if they are not
    // inline expanded. Libraries of templates are thus sometimes called "header-only" libraries
    // since they do not require any *.cpp files.
    //
    cout << "The minimum is " << vtsu::min( s1, s2 ) << endl;

    cout << "Enter an int and a double 'a' and 'x': ";
    cin >> a;
    cin >> x;

    // This usage of the template is an error because there is no single type `T` that can be
    // deduced from the arguments (int and double). The template requires that both arguments
    // have the same type, and that isn't true here.
    //
    cout << "The minimum is " << vtsu::min( a, x ) << endl;

    // The problem could be worked around by expliciting converting one of the arguments.
    //cout << "The minimum is " << vtsu::min( static_cast<double>( a ), x ) << endl;

    // The problem could also be worked around by explicitly specifying T and then let the
    // compiler do an implicit type conversion of the other argument.
    //cout << "The minimum is " << vtsu::min<double>( a, x ) << endl;

    // ... or the template could be defined to take two type parameters with an inferred return
    // type.
    //cout << "The minimum is " << vtsu::min2( a, x ) << endl;

    // .. or the template could be defined using auto parameters, a C++ 2020 feature.
    //cout << "The minimum is " << vtsu::min3( a, x ) << endl;

    return EXIT_SUCCESS;
}
