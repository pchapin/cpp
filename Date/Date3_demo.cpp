
#include <cstdlib>    // Needed for EXIT_SUCCESS (and EXIT_FAILURE).
#include <iomanip>    // Needed for manipulators with parameters.
#include <iostream>
#include <stdexcept>  // Needed for exception classes.
#include "Date3.hpp"

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

        // Here the 'right' manipulator calls for right justification of the output field.
        // Note that some manipulators, such as 'right' and 'setw' affect only the next output
        // field. Other manipulators, such as 'setfill' affect all subsequent output fields.
        cout << setfill( '*' );
        cout << "|" << right << setw(20) << tomorrow << "|" << endl;

        // Check to see if the fill character is still '*' (and not '0').
        cout << "|" << left << setw(20) << 42 << "|" << endl;

        // Ask about birthdays.
        vtsu::Date user1_birthday;
        vtsu::Date user2_birthday;
        cout << "What is your birthday? ";
        cin >> user1_birthday;
        cout << "What is your friend's birthday? ";
        cin >> user2_birthday;
        if( user1_birthday < user2_birthday ) {
            cout << "You are older than your friend by "
                 << vtsu::difference( user2_birthday, user1_birthday ) << " days." << endl;
        }
        else if( user1_birthday > user2_birthday ) {
            cout << "You are younger than your friend by "
                 << vtsu::difference( user1_birthday, user2_birthday ) << " days." << endl;
        }
        else {
            cout << "You and your friend are the same age." << endl;
        }

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
