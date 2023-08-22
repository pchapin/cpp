/*! \file    bubble_demo.cpp
 *  \brief   A program that demonstrates the use of the bubble_sort template.
 *  \author  Peter Chapin <peter.chapin@vermontstate.edu>
 * 
 * This file is used in CIS-3012, the C++ Programming class at Vermont State University.
 */

#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "bubble_sort.hpp"

using namespace std;

int main( )
{
    // Declare various entities that are sequences of things.
    int array1[] = { 4, 6, 1, 7, 3, 9 };
    std::string array2[] = { "hello", "world", "zebra", "apple" };
    std::vector<int> my_vector{ 4, 6, 1, 7, 3, 9 };
    std::list<int> my_list{ 4, 6, 1, 7, 3, 9 };

    // Sort them all and print them out. The compiler creates a fresh instantiation of the
    // bubble_sort template for each data type required. Since both ints and strings have a
    // suitable operator< defined, the instantiation of bubble_sort succeeds in every case.
    // Notice that the various library containers also have suitable iterator types defined (and
    // all are at least as powerful as forward iterators).

    cout << "\nSorting array1..." << endl;
    bubble_sort( array1, array1 + 6 );

    for( int element : array1 ) {
        cout << element << endl;
    }

    cout << "\nSorting array2..." << endl;
    bubble_sort( array2, array2 + 4 );

    for( const string &element : array2 ) {
        cout << element << endl;
    }

    cout << "\nSorting my_vector..." << endl;
    bubble_sort( my_vector.begin(), my_vector.end() );

    for( int element : my_vector ) {
        cout << element << endl;
    }

    cout << "\nSorting my_list..." << endl;
    bubble_sort( my_list.begin(), my_list.end() );

    for( int element : my_list ) {
        cout << element << endl;
    }

    // Now sort array1 in descending order. This time we need to provide a comparison function
    // object. We will use the library std::greater functor template specialized for int.
    cout << "\nSorting array1 in descending order..." << endl;
    bubble_sort( array1, array1 + 6, std::greater<int>( ) );

    for( int element : array1 ) {
        cout << element << endl;
    }

    return EXIT_SUCCESS;
}
