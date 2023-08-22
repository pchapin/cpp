
#include <iostream>
#include <string>
#include "Option.hpp"

using namespace std;

Option<unsigned> process_string( const Option<string> &s )
{
    // Filter out all strings with a length greater than or equal to 10.
    Option<string> s1 = s.filter( [](const string &x) { return x.length() < 10; } );

    // Transform the string into its length. Note that we must explicitly provide the type of U
    // since the compiler can't deduce that type when it is only used in the return type.
    return s1.transform<unsigned>( [](const string &x) { return x.length(); } );
}


int main( )
{
    Option<string> s( "Hello!" );
    Option<unsigned> result = process_string( s );

    cout << "Result = " << result.get( ) << "\n";
}
