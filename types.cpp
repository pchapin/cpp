/*! \file    types.cpp
 *  \brief   Sample program that illustrates the sizes and ranges of various primitive types.
 *  \author  Peter Chapin <peter.chapin@vermontstate.edu>
 *
 *  This program displays information about the arithmetic types built into the compiler.
 *  Compile using a command such as, for example:
 *
 *      $ g++ -Wall -std=c++20 -o types types.cpp
 */

#include <iomanip>
#include <iostream>
#include <limits>

using namespace std;

template<typename Character>
void display_character_information( const char *type_name )
{
    cout << setw(11) << (int)numeric_limits<Character>::min( )
         << " <= "   << setw(13) << type_name << " <= "
         << setw(11) << (int)numeric_limits<Character>::max( )
         << "  ("    << setw(2) << sizeof( Character ) << " bytes)"
         << "\n";
}


template<typename Integer>
void display_integer_information( const char *type_name )
{
    cout << setw(20) << numeric_limits<Integer>::min( )
         << " <= "   << setw(18) << type_name << " <= "
         << setw(20) << numeric_limits<Integer>::max( )
         << "  ("    << setw(2) << sizeof( Integer ) << " bytes)"
         << "\n";
}


template<typename Float>
void display_floating_information( const char *type_name )
{
    cout << setprecision( numeric_limits<Float>::digits10 );
    cout << type_name << "\n";
    cout << "\tbytes          = " << sizeof( Float ) << "\n";
    cout << "\tmin            = " << numeric_limits<Float>::min( )         << "\n";
    cout << "\tmax            = " << numeric_limits<Float>::max( )         << "\n";
    cout << "\tdigits10       = " << numeric_limits<Float>::digits10       << "\n";
    cout << "\tmin_exponent10 = " << numeric_limits<Float>::min_exponent10 << "\n";
    cout << "\tmax_exponent10 = " << numeric_limits<Float>::max_exponent10 << "\n";
    cout << "\tepsilon        = " << numeric_limits<Float>::epsilon( )     << "\n";
    cout << "\n";
}

int main( )
{
    cout << "CHARACTER TYPES\n";
    cout << "---------------\n";
    display_character_information<char>         ( "char"            );
    display_character_information<signed char>  ( "signed char"     );
    display_character_information<unsigned char>( "unsigned char"   );
    display_character_information<wchar_t>      ( "wchar_t"         );
    
    cout << "\n\n";
    cout << "INTEGER TYPES\n";
    cout << "-------------\n";
    display_integer_information<short>         ( "short"          );
    display_integer_information<unsigned short>( "unsigned short" );
    display_integer_information<int>           ( "int"            );
    display_integer_information<unsigned int>  ( "unsigned int"   );
    display_integer_information<long>          ( "long"           );
    display_integer_information<unsigned long> ( "unsigned long"  );
    display_integer_information<long long>     ( "long long"      );
    display_integer_information<unsigned long long>( "unsigned long long" );

    cout << "\n\n";
    cout << "POINTER TYPES\n";
    cout << "-------------\n";
    cout << "sizeof( void * ) == " << sizeof( void * ) << "\n";
    
    cout << "\n\n";
    cout << "TYPE ALIASES\n";
    cout << "------------\n";
    display_integer_information<size_t>   ( "size_t"    );
    display_integer_information<ptrdiff_t>( "ptrdiff_t" );
    
    cout << "\n\n";
    cout << "FLOATING POINT TYPES\n";
    cout << "--------------------\n";
    display_floating_information<float>      ( "float"       );
    display_floating_information<double>     ( "double"      );
    display_floating_information<long double>( "long double" );
    return 0;
}

