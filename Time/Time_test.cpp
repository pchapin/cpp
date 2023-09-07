/*! \file    Time_test.cpp
 *  \brief   Test program for vtsu::Time.
 *  \author  Peter Chapin <peter.chapin@vermontstate.edu>
 * 
 * This class is a homework assignment for CIS-3012, the C++ Programming class at Vermont State
 * University.
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include "Time.hpp"

using namespace std;
// using namespace vtsu;

// Helper function to generate a message string that includes the file name and line number.
string message_helper( const string &message, const string &file, int line )
{
    return message + " (" + file + ":" + to_string( line ) + ")";
}


// Constructor tests.
void test1( )
{
    std::cout << "Constructor Time( ) ... ";
    vtsu::Time t1;
    if ( !( t1.get_hours( ) == 0U && t1.get_minutes( ) == 0U && t1.get_seconds( ) == 0U ) ) {
        throw runtime_error( message_helper( "Default constructor failed", __FILE__, __LINE__ ) );
    }
    std::cout << "OK" << endl;

    // Implementation Note: This style of executing tests is highly repetitive. It is better, to
    // define structures to hold test cases and expected results. The test function then becomes
    // a loop that iterates over the test cases. Adding a new test case is then as simple as
    // adding new entries to the structures. This is left as an exercise for the reader (but see
    // the other test functions below). :)

    std::cout << "Constructor Time( unsigned, unsigned, unsigned ) ... ";
    vtsu::Time u1{ 23U, 59U, 59U };
    if ( !( u1.get_hours( ) == 23U && u1.get_minutes( ) == 59U && u1.get_seconds( ) == 59U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time u2{ 24U, 60U, 60U };
    if ( !( u2.get_hours( ) == 1U && u2.get_minutes( ) == 1U && u2.get_seconds( ) == 0U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time u3{ 0U, 1U, 500U };
    if ( !( u3.get_hours( ) == 0U && u3.get_minutes( ) == 9U && u3.get_seconds( ) == 20U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time u4{ 0U, 0U, 86400U };
    if ( !( u4.get_hours( ) == 0U && u4.get_minutes( ) == 0U && u4.get_seconds( ) == 0U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time u5{ 0U, 0U, 86401U };
    if ( !( u5.get_hours( ) == 0U && u5.get_minutes( ) == 0U && u5.get_seconds( ) == 1U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time u6{ 0U, 0U, 86900U };
    if ( !( u6.get_hours( ) == 0U && u6.get_minutes( ) == 8U && u6.get_seconds( ) == 20U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    std::cout << "OK" << endl;

    std::cout << "Constructor Time( const string & ) ... ";
    vtsu::Time v0{ "beep:bop:boop" };
    if ( !( v0.get_hours( ) == 0U && v0.get_minutes( ) == 0U && v0.get_seconds( ) == 0U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time v1{ "23:59:59" };
    if ( !( v1.get_hours( ) == 23U && v1.get_minutes( ) == 59U && v1.get_seconds( ) == 59U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time v2{ "24:60:60" };
    if ( !( v2.get_hours( ) == 1U && v2.get_minutes( ) == 1U && v2.get_seconds( ) == 0U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time v3{ "0:1:500" };
    if ( !( v3.get_hours( ) == 0U && v3.get_minutes( ) == 9U && v3.get_seconds( ) == 20U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time v4{ "0:0:86400" };
    if ( !( v4.get_hours( ) == 0U && v4.get_minutes( ) == 0U && v4.get_seconds( ) == 0U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time v5{ "0:0:86401" };
    if ( !( v5.get_hours( ) == 0U && v5.get_minutes( ) == 0U && v5.get_seconds( ) == 1U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    vtsu::Time v6{ "0:0:86900" };
    if ( !( v6.get_hours( ) == 0U && v6.get_minutes( ) == 8U && v6.get_seconds( ) == 20U ) ) {
        throw runtime_error( message_helper( "Constructor failed", __FILE__, __LINE__ ) );
    }
    std::cout << "OK" << endl;
}


void test2( )
{
    struct TestCase {
        vtsu::Time left;
        vtsu::Time right;
        int        expected_difference;
    };

    TestCase test_cases[] = {
        { vtsu::Time( "00:00:00" ), vtsu::Time( "00:00:00" ),      0 },
        { vtsu::Time( "00:00:01" ), vtsu::Time( "00:00:00" ),      1 },
        { vtsu::Time( "00:00:00" ), vtsu::Time( "00:01:00" ),    -60 },
        { vtsu::Time( "01:00:00" ), vtsu::Time( "00:00:00" ),  3'600 },
        { vtsu::Time( "00:01:00" ), vtsu::Time( "00:00:50" ),     10 },
        { vtsu::Time( "00:50:00" ), vtsu::Time( "01:00:00" ),   -600 },
        { vtsu::Time( "23:59:59" ), vtsu::Time( "00:00:00" ), 86'399 }
    };
    
    std::cout << "operator-( ) ... ";
    for( const auto &test_case : test_cases ) {
        if( ( test_case.left - test_case.right ) != test_case.expected_difference ) {
            throw runtime_error( message_helper( "Subtraction test failed", __FILE__, __LINE__ ) );
        }
    }
    std::cout << "OK" << endl;
}


void test3( )
{
    struct TestCase {
        vtsu::Time time;
        unsigned   delta;
        vtsu::Time expected;
    };

    TestCase hours_cases[] = {
        { vtsu::Time( "00:00:00" ),  1, vtsu::Time( "01:00:00" ) },
        { vtsu::Time( "00:00:00" ), 23, vtsu::Time( "23:00:00" ) },
        { vtsu::Time( "00:00:00" ), 24, vtsu::Time( "00:00:00" ) },
        { vtsu::Time( "00:00:00" ), 25, vtsu::Time( "01:00:00" ) },
        { vtsu::Time( "00:00:00" ), 48, vtsu::Time( "00:00:00" ) },
        { vtsu::Time( "00:00:00" ), 49, vtsu::Time( "01:00:00" ) },
        { vtsu::Time( "11:22:33" ),  1, vtsu::Time( "12:22:33" ) }
    };

    TestCase minutes_cases[] = {
        { vtsu::Time( "00:00:00" ),   1, vtsu::Time( "00:01:00" ) },
        { vtsu::Time( "00:00:00" ),  59, vtsu::Time( "00:59:00" ) },
        { vtsu::Time( "00:00:00" ),  60, vtsu::Time( "00:00:00" ) },
        { vtsu::Time( "00:00:00" ),  61, vtsu::Time( "00:01:00" ) },
        { vtsu::Time( "00:00:00" ), 120, vtsu::Time( "00:00:00" ) },
        { vtsu::Time( "00:00:00" ), 121, vtsu::Time( "00:01:00" ) },
        { vtsu::Time( "11:22:33" ),   1, vtsu::Time( "11:23:33" ) }
    };

    TestCase seconds_cases[] = {
        { vtsu::Time( "00:00:00" ),     1, vtsu::Time( "00:00:01" ) },
        { vtsu::Time( "00:00:00" ),    59, vtsu::Time( "00:00:59" ) },
        { vtsu::Time( "00:00:00" ),    60, vtsu::Time( "00:00:00" ) },
        { vtsu::Time( "00:00:00" ),    61, vtsu::Time( "00:00:01" ) },
        { vtsu::Time( "00:00:00" ),   120, vtsu::Time( "00:00:00" ) },
        { vtsu::Time( "00:00:00" ),   121, vtsu::Time( "00:00:01" ) },
        { vtsu::Time( "11:22:33" ),     1, vtsu::Time( "11:22:34" ) },
        { vtsu::Time( "00:00:00" ), 86400, vtsu::Time( "00:00:00" ) },
        { vtsu::Time( "00:00:00" ), 86401, vtsu::Time( "00:00:01" ) }
    };

    std::cout << "roll_forward_hours ... ";
    for( const auto &hours_case : hours_cases ) {
        if( hours_case.time.roll_forward_hours( hours_case.delta ) != hours_case.expected ) {
            throw runtime_error( message_helper( "roll_forward_hours( ) test failed", __FILE__, __LINE__ ) );
        }
    }
    std::cout << "OK" << endl;

    std::cout << "roll_forward_minutes ... ";
    for( const auto &minutes_case : minutes_cases ) {
        if( minutes_case.time.roll_forward_minutes( minutes_case.delta ) != minutes_case.expected ) {
            throw runtime_error( message_helper( "roll_forward_minutes( ) test failed", __FILE__, __LINE__ ) );
        }
    }
    std::cout << "OK" << endl;

    std::cout << "roll_forward_seconds ... ";
    for( const auto &seconds_case : seconds_cases ) {
        if( seconds_case.time.roll_forward_seconds( seconds_case.delta ) != seconds_case.expected ) {
            throw runtime_error( message_helper( "roll_forward_seconds( ) test failed", __FILE__, __LINE__ ) );
        }
    }
    std::cout << "OK" << endl;
}


void test4( )
{
    struct TestCase {
        vtsu::Time left;
        vtsu::Time right;
        bool       expected_equals;
        bool       expected_not_equals;
        bool       expected_less_than;
        bool       expected_less_than_or_equal;
        bool       expected_greater_than;
        bool       expected_greater_than_or_equal;
    };

    TestCase test_cases[] = {
        { vtsu::Time( "00:00:00" ), vtsu::Time( "00:00:00" ), true, false, false, true, false, true },
        { vtsu::Time( "00:00:01" ), vtsu::Time( "00:00:00" ), false, true, false, false, true, true },
        { vtsu::Time( "00:00:00" ), vtsu::Time( "00:01:00" ), false, true, true, true, false, false },
        { vtsu::Time( "01:00:00" ), vtsu::Time( "00:00:00" ), false, true, false, false, true, true },
        { vtsu::Time( "00:01:00" ), vtsu::Time( "00:00:50" ), false, true, false, false, true, true },
        { vtsu::Time( "00:50:00" ), vtsu::Time( "01:00:00" ), false, true, true, true, false, false }
    };

    std::cout << "Relational Operators ... ";
    for( const auto &test_case : test_cases ) {
        if( ( test_case.left == test_case.right ) != test_case.expected_equals ) {
            throw runtime_error( message_helper( "Equality test failed", __FILE__, __LINE__ ) );
        }
        if( ( test_case.left != test_case.right ) != test_case.expected_not_equals ) {
            throw runtime_error( message_helper( "Inequality test failed", __FILE__, __LINE__ ) );
        }
        if( ( test_case.left < test_case.right ) != test_case.expected_less_than ) {
            throw runtime_error( message_helper( "Less than test failed", __FILE__, __LINE__ ) );
        }
        if( ( test_case.left <= test_case.right ) != test_case.expected_less_than_or_equal ) {
            throw runtime_error( message_helper( "Less than or equal test failed", __FILE__, __LINE__ ) );
        }
        if( ( test_case.left > test_case.right ) != test_case.expected_greater_than ) {
            throw runtime_error( message_helper( "Greater than test failed", __FILE__, __LINE__ ) );
        }
        if( ( test_case.left >= test_case.right ) != test_case.expected_greater_than_or_equal ) {
            throw runtime_error( message_helper( "Greater than or equal test failed", __FILE__, __LINE__ ) );
        }
    }
    std::cout << "OK" << endl;
}


void test5( )
{
    struct TestCase {
        vtsu::Time time;
        string     expected;
    };

    TestCase test_cases[] = {
        { vtsu::Time( "00:00:00" ), "00:00:00" },
        { vtsu::Time( "00:00:01" ), "00:00:01" },
        { vtsu::Time( "00:01:00" ), "00:01:00" },
        { vtsu::Time( "01:00:00" ), "01:00:00" },
        { vtsu::Time( "00:01:01" ), "00:01:01" },
        { vtsu::Time( "01:01:00" ), "01:01:00" },
        { vtsu::Time( "01:01:01" ), "01:01:01" }
    };

    std::cout << "operator<<( ) ... ";
    for( const auto &test_case : test_cases ) {
        ostringstream stream;
        stream << test_case.time;
        if( stream.str( ) != test_case.expected ) {
            throw runtime_error( message_helper( "operator<<( ) test failed", __FILE__, __LINE__ ) );
        }
    }
    std::cout << "OK" << endl;
}


int main( )
{
    try {
        test1( );  // Tests for constructors.
        test2( );  // Tests for operator-( )
        test3( );  // Tests for the roll_forward_* methods.
        test4( );  // Tests for relational operators.
        test5( );  // Tests for operator<<( )
        return EXIT_SUCCESS;
    }
    catch ( const exception &e ) {
        cerr << "\n\nUnhandled exception: " << e.what( ) << endl;
        return EXIT_FAILURE;
    }
    catch ( ... ) {
        cerr << "\n\nUnknown exception" << endl;
        return EXIT_FAILURE;
    }
}
