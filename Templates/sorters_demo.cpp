
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "sorters_2.hpp"

using namespace std;

bool my_ordering( int x, int y )
{
    return x > y;
}

struct MyOtherOrdering {
    bool operator()( int x, int y );
};


bool MyOtherOrdering::operator()( int x, int y )
{
    bool xIsEven = (x % 2) == 0;
    bool yIsEven = (y % 2) == 0;

    if( xIsEven && yIsEven) {
        return x < y;
    }
    else if( xIsEven && !yIsEven) {
        return true;
    }
    else if( !xIsEven && yIsEven) {
        return false;
    }
    else {
        return x > y;
    }
}

struct less {
    bool operator()( int x, int y ) { return x < y; }
};


int main( )
{
    MyOtherOrdering strange_order;
    
    // Declare various entities that are sequences of things.
    int array1[] = { 4, 6, 1, 7, 3, 9 };
    std::string array2[] = { "hello", "world", "zebra", "apple" };
    std::vector<int> my_vector = { 4, 6, 1, 7, 3, 9 };
    std::list<int> my_list = { 4, 6, 1, 7, 3, 9 };

    // Sort them all and print them out. The compiler creates a fresh instantiation of the
    // bubble_sort template for each data type required. Since both ints and strings have a
    // suitable operator< defined, the instantiation of bubble_sort succeeds in every case.
    // Notice that the various library containers also have suitable iterator types defined (and
    // all are at least as powerful as forward iterators).

    cout << "\nSorting array1..." << endl;
    // vtsu::bubble_sort( array1, array1 + 6 );
    vtsu::bubble_sort( begin( array1 ), end( array1 ) );

    for( int element : array1 ) {
        cout << element << endl;
    }

    cout << "\nSorting array1 in a custom order..." << endl;
    // vtsu::bubble_sort( array1, array1 + 6, my_ordering );
    vtsu::bubble_sort( begin( array1 ), end( array1 ), my_ordering );

    for( int element : array1 ) {
        cout << element << endl;
    }

    cout << "\nSorting array1 in a weird order..." << endl;
    // vtsu::bubble_sort( array1, array1 + 6, strange_order );
    vtsu::bubble_sort( begin( array1 ), end( array1 ), strange_order );

    for( int element : array1 ) {
        cout << element << endl;
    }

    cout << "\nSorting array2..." << endl;
    // vtsu::bubble_sort( array2, array2 + 4 );
    vtsu::bubble_sort( begin( array2 ), end( array2 ) );

    for( const string &element : array2 ) {
        cout << element << endl;
    }

    cout << "\nSorting my_vector..." << endl;
    // vtsu::bubble_sort( my_vector.begin(), my_vector.end() );
    vtsu::bubble_sort( begin( my_vector ), end( my_vector ) );

    for( int element : my_vector ) {
        cout << element << endl;
    }

    cout << "\nSorting my_list..." << endl;
    // vtsu::bubble_sort( my_list.begin(), my_list.end() );
    vtsu::bubble_sort( begin( my_list ), end( my_list ) );

    for( int element : my_list ) {
        cout << element << endl;
    }

    cout << "\nSorting array1 in descending order..." << endl;
    // vtsu::bubble_sort( array1, array1 + 6, std::greater<int>( ) );
    vtsu::bubble_sort( begin( array1 ), end( array1 ), std::greater<int>( ) );

    for( int element : array1 ) {
        cout << element << endl;
    }

    return EXIT_SUCCESS;
}
