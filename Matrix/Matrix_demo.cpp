/*! \file   Matrix.hpp
 *  \brief  A program that demonstrates the Matrix template.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "Matrix.hpp"

using namespace std;

void simple_constructor_check( )
{
    cout << "Simple constructor check..." << endl;

    vtsu::Matrix<int> m1( 3, 2 );
    cout << "dimension = (" << m1.rows( ) << ", " << m1.columns( ) << ")" << endl;
    cout << m1 << endl;

    cout << "... checking exceptions..." << endl;
    try {
        vtsu::Matrix<int> m2( 0, 2 );
    }
    catch( const vtsu::Matrix<int>::InvalidSize &error ) {
        cout << "Caught exception: " << error.what( ) << " (expected)" << endl;
    }

    try {
        vtsu::Matrix<int> m2( 3, 0 );
    }
    catch( const vtsu::Matrix<int>::InvalidSize &error ) {
        cout << "Caught exception: " << error.what( ) << " (expected)" << endl;
    }
    cout << endl;
}


void initializer_list_constructor_check( )
{
    cout << "Initializer list constructor check..." << endl;

    vtsu::Matrix<int> m2 =
        {
            { 1, 2, 3 },
            { 4, 5, 6 }
        };
    cout << "dimension = (" << m2.rows( ) << ", " << m2.columns( ) << ")" << endl;
    cout << m2 << endl;

    vtsu::Matrix<int> m_ragged =
        {
             { 1, 2, 3 },
             { 4, 5 },
             { 6, 7, 8, 9 }
        };
    cout << "dimension = (" << m_ragged.rows( ) << ", " << m_ragged.columns( ) << ")" << endl;
    cout << m_ragged << endl;

    cout << "... checking exceptions..." << endl;
    try {
        vtsu::Matrix<int> m_zero_rows =
            {
            };
    }
    catch( const vtsu::Matrix<int>::InvalidSize &error ) {
        cout << "Caught exception: " << error.what( ) << " (expected)" << endl;
    }

    try {
        vtsu::Matrix<int> m_zero_columns =
            {
                { },
                { },
                { }
            };
    }
    catch( const vtsu::Matrix<int>::InvalidSize &error ) {
        cout << "Caught exception: " << error.what( ) << " (expected)" << endl;
    }
    cout << endl;
}


void access_check( )
{
    cout << "Access check..." << endl;

    vtsu::Matrix<double> m3 =
        {
            { 1.0, 2.0, 3.0 },
            { 4.0, 5.0, 6.0 },
            { 7.0, 8.0, 9.0 }
        };

    cout << "dimension = (" << m3.rows( ) << ", " << m3.columns( ) << ")" << endl;

    // Print the matrix.
    cout << fixed;
    cout << setprecision( 3 );
    for( vtsu::Matrix<double>::index_type i = 0; i < m3.rows( ); ++i ) {
        for( vtsu::Matrix<double>::index_type j = 0; j < m3.columns( ); ++j ) {
            cout << "m3(" << i << ", " << j << ") = " << m3( i, j ) << endl;
        }
    }
    cout << endl;

    cout << "... checking exceptions..." << endl;
    try {
        m3( 3, 0 ) = 0.0;
    }
    catch( const vtsu::Matrix<double>::OutOfBoundsIndex &error ) {
        cout << "Caught exception: " << error.what( ) << " (expected)" << endl;
    }

    try {
        m3( 0, 3 ) = 0.0;
    }
    catch( const vtsu::Matrix<double>::OutOfBoundsIndex &error ) {
        cout << "Caught exception: " << error.what( ) << " (expected)" << endl;
    }
    cout << endl;
}


int main( )
{
    simple_constructor_check( );
    initializer_list_constructor_check( );
    access_check( );

    return EXIT_SUCCESS;
}
