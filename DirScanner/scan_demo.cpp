/****************************************************************************
FILE          : scan_demo.cpp
LAST REVISION : 2007-09-08
SUBJECT       : Program to demonstrate directory scanners.
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include <cstdlib>
#include <iostream>
#include "d_scanner.h"

using namespace std;

int main( int argc, char **argv )
{
    // Check the command line.
    if( argc != 2 ) {
        cerr << "Usage: " << argv[0] << " directory_name\n";
        return( EXIT_FAILURE );
    }

    // Do the scan.
    D_Scanner scanner( argv[1] );
    while( scanner.has_more( ) ) {
        cout << scanner.get( ) << "\n";
        scanner.next( );
    }
    scanner.close( );
    
    return( EXIT_SUCCESS );
}
