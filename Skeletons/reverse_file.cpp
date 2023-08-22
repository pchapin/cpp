/*! \file   reverse_file.cpp
 *  \brief  A simple program that processes (filters) the text at its standard input.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 *
 * This program reverses the order of the lines at standard input. It outputs the last line
 * first, and so forth.
 */

#include <algorithm> // Needed for the reverse algorithm.
#include <cstdlib>   // The C++ library version of the C standard header stdlib.h.
#include <iostream>  // The C++ I/O library.
#include <string>    // Provides C++ strings.
#include <vector>    // Provides C++ vectors (dynamically expandable arrays).

using namespace std;

int main( )
{
    string line;          // Default constructed to an empty string with no characters.
    vector<string> text;  // Default constructed to an empty vector with no elements.

    // Read the entire input at the standard input device and store it in 'text'.
    while( getline( cin, line ) ) {
        text.push_back( line );  // Appends 'line' to the vector. The vector grows as needed.
    }

    // Reverse the order of the elements of the 'text' vector.
    reverse( text.begin( ), text.end( ) );

    // Print the resulting text vector using a C++ range-based for loop.
    for( const auto &item : text ) {
        cout << item << endl;
    }
    return EXIT_SUCCESS;
}
