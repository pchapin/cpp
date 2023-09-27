/*! \file   Matrix.hpp
 *  \brief  A program that demonstrates the Matrix template.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "Matrix.hpp"

using namespace std;

int main( )
{
    vtsu::Matrix<double> m =
        {
            { 1.0, 2.0, 3.0 },
            { 4.0, 5.0, 6.0 },
            { 7.0, 8.0, 9.0 }
        };

    cout << "dimension = (" << m.rows( ) << ", " << m.columns( ) << ")" << endl;

    // Print the matrix.
    cout << fixed;
    cout << setprecision( 3 );
    for( vtsu::Matrix<double>::index_type i = 0; i < m.rows( ); ++i ) {
        for( vtsu::Matrix<double>::index_type j = 0; j < m.columns( ); ++j ) {
            cout << "m(" << i << ", " << j << ") = " << m( i, j ) << endl;
        }
    }
    cout << endl;

    // ... or just use the overloaded insertion operator!
    cout << m;

    return EXIT_SUCCESS;
}
