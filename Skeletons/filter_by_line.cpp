/*! \file   filter_by_line.cpp
 *  \brief  Skeleton program that reads standard input a line at a time.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main( )
{
    string line;

    while( getline( cin, line ) ) {
        // Process line...

        cout << line << endl;
    }

    return EXIT_SUCCESS;
}
