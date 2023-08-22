/*! \file   Interval_demo.cpp
 *  \brief  A program that demonstrates class Interval by implementing a simple four function calculator.
 *  \author Peter C. Chapin <pchapin@vtc.edu>
 */

#include <cstdlib>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

#include "Interval.hpp"

using namespace std;

int main( )
{
    string line;
    vtc::Interval right ( 0.0, 0.0 );
    vtc::Interval left  ( 0.0, 0.0 );
    vtc::Interval result( 0.0, 0.0 );
    list<vtc::Interval> interval_stack;

    cout << "> " << flush;
    while( getline( cin, line ) ) {
        if( line.length( ) == 0 ) break;

        switch( line[0] ) {
        case '+':
            right = interval_stack.front( ); interval_stack.pop_front( );
            left  = interval_stack.front( ); interval_stack.pop_front( );
            result = left + right;
            interval_stack.push_front( result );
            cout << interval_stack.front( ) << endl;
            break;

        case '-':
            right = interval_stack.front( ); interval_stack.pop_front( );
            left  = interval_stack.front( ); interval_stack.pop_front( );
            result = left - right;
            interval_stack.push_front( result );
            cout << interval_stack.front( ) << endl;
            break;

        case '*':
            right = interval_stack.front( ); interval_stack.pop_front( );
            left  = interval_stack.front( ); interval_stack.pop_front( );
            result = left * right;
            interval_stack.push_front( result );
            cout << interval_stack.front( ) << endl;
            break;

        case '/':
            right = interval_stack.front( ); interval_stack.pop_front( );
            left  = interval_stack.front( ); interval_stack.pop_front( );
            result = left / right;
            interval_stack.push_front( result );
            cout << interval_stack.front( ) << endl;
            break;

        default: {
                istringstream scanner( line );
                scanner >> result;
                interval_stack.push_front( result );
            }
            break;
        }

         cout << "> " << flush;
    }
    return EXIT_SUCCESS;
}