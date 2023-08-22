
#include <cstdlib>
#include <iomanip>
#include <iostream>
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

    // Implementation Note: This style of executing tests is highly repetitive. It is better,
    // but requires more work, to define structures to hold test cases and expected results. The
    // test function then becomes a loop that simply iterates over the test cases. Adding a new
    // test case is then as simple as adding new entries to the structures. This is left as an
    // exercise for the reader. :)

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
    vtsu::Time v0{ "beep:bop:foo" };
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

int main( )
{
    try {
        test1( );
        // TODO: Write tests for operator-( )
        // TODO: Write tests for the roll_forward_* methods.
        // TODO: Write tests for relational operators.
        // TODO: Write tests for operator<<( )
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
