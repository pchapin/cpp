/*! \file   filter_by_char.cpp
 *  \brief  Skeleton program that reads standard input a character at a time.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iostream>

using namespace std;

int main( )
{
    char ch;

    while( cin.get( ch ) ) {
        // Process ch...

        cout.put( ch );
    }

    return EXIT_SUCCESS;
}
