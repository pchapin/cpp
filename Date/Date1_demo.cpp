
#include <cstdlib>    // Needed for EXIT_SUCCESS (and EXIT_FAILURE).
#include <iomanip>    // Needed for manipulators with parameters.
#include <iostream>
#include <stdexcept>  // Needed for exception classes.
#include "Date1.hpp"

using namespace std;
// using namespace vtsu;

int main( )
{
    try {
        // NOTE: C++ 2020 allows designated initializers, but not for non-aggregate types.
        // NOTE: C++ 2020 does *not* allow keyword arguments.
        vtsu::Date today{ 2020, 9, 15 };
        vtsu::Date tomorrow{ today };
        tomorrow.advance( );

        cout << setfill( '*' );
        cout << "|" << setw(20) << tomorrow << "|" << endl;

        // Check to see if the fill character is still '*' (and not '0').
        cout << "|" << setw(20) << 42 << "|" << endl;

        // Do something bad!
        // First, because of the 400 year rule, 2000 *is* a leap year.
        today.set( "2000-02-29" ); // OK
        if( today != vtsu::Date{ 2000, 2, 29 } ) {
            cerr << "ERROR: today != vtsu::Date{ 2000, 2, 29 }" << endl;
            return EXIT_FAILURE;
        }

        // However, because of the 100 year rule, 2100 is not a leap year.
        today.set( "2100-02-29" ); // Throws vtsu::Date::Invalid exception.

        return EXIT_SUCCESS;
    }
    catch ( const exception &e ) {
        cerr << "Unhandled exception: " << e.what( ) << endl;
        return EXIT_FAILURE;
    }
    catch ( ... ) {
        cerr << "Unknown exception" << endl;
        return EXIT_FAILURE;
    }
}
