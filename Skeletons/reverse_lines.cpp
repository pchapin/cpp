/*! \file   reverse_lines.cpp
 *  \brief  A simple program that processes (filters) the text at its standard input.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 *
 * This program reverses the text of each line of its input using a library algorithm template.
 */

#include <algorithm> // Needed for the reverse algorithm.
#include <cstdlib>   // The C++ library version of the C standard header stdlib.h.
#include <iostream>  // The C++ I/O library.
#include <string>    // Provides C++ strings.

using namespace std;

int main( )
{
    string line;

    while( getline( cin, line ) ) {
        reverse( line.begin( ), line.end( ) );
        cout << line << endl;
    }
    return EXIT_SUCCESS;
}
