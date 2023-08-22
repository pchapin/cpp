/****************************************************************************
FILE          : f_tables.cpp
LAST REVISION : 2007-09-16
SUBJECT       : Program that prints addition and multiplication tables.
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "rational.h"

using namespace std;
using namespace VTC;

void create_addition_table( ostream &os )
{
    Rational x, y;

    // Print header.
    os << "     || ";
    for( int i = 1; i <= 12; ++i ) {
        y = Rational( i, 12 );
        os << y << " | ";
    }
    os << "\n";
    
    for( int i = 1; i <= 12; ++i ) {
        x = Rational( i, 12 );
        os << x << " || ";
        for( int j = 1; j <= 12; ++j ) {
            y = Rational( j, 12 );
            os << x + y << " | ";
        }
        os << "\n";
    }
    os << "\n";
}


void create_multiplication_table( ostream &os )
{
    Rational x, y;
    
    // Print header.
    os << "     || ";
    for( int i = 1; i <= 12; ++i ) {
        y = Rational( i, 12 );
        os << y << " | ";
    }
    os << "\n";
    
    for( int i = 1; i <= 12; ++i ) {
        x = Rational( i, 12 );
        os << x << " || ";
        for( int j = 1; j <= 12; ++j ) {
            y = Rational( j, 12 );
            os << x * y << " | ";
        }
        os << "\n";
    }
    os << "\n";
}


int main( int argc, char **argv )
{
    if( argc != 2 ) {
        cerr << "USAGE: " << argv[0] << " file_name\n";
        return EXIT_FAILURE;
    }

    ofstream output( argv[1] );
    if( !output ) {
        cerr << "Could not open " << argv[1] << " for writing.\n";
        return EXIT_FAILURE;
    }

    output << "ADDITION TABLE\n==============\n";
    create_addition_table( output );

    output << "MULTIPLICATION TABLE\n====================\n";
    create_multiplication_table( output );
    return EXIT_SUCCESS;
}
