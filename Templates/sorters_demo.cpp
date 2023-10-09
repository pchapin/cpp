
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

    cout << "\nSorting array1...\n";
    vtsu::bubble_sort( array1, array1 + 6 );

    for( int element : array1 ) {
        cout << element << "\n";
    }

    cout << "\nSorting array1 in a custom order...\n";
    vtsu::bubble_sort( array1, array1 + 6, my_ordering );

    for( int element : array1 ) {
        cout << element << "\n";
    }

    cout << "\nSorting array1 in a weird order...\n";
    vtsu::bubble_sort( array1, array1 + 6, strange_order );

    for( int element : array1 ) {
        cout << element << "\n";
    }

    cout << "\nSorting array2...\n";
    vtsu::bubble_sort( array2, array2 + 4 );

    for( const string &element : array2 ) {
        cout << element << "\n";
    }

    cout << "\nSorting my_vector...\n";
    vtsu::bubble_sort( my_vector.begin(), my_vector.end() );

    for( int element : my_vector ) {
        cout << element << "\n";
    }

    cout << "\nSorting my_list...\n";
    vtsu::bubble_sort( my_list.begin(), my_list.end() );

    for( int element : my_list ) {
        cout << element << "\n";
    }

    cout << "\nSorting array1 in descending order...\n";
    vtsu::bubble_sort( array1, array1 + 6, std::greater<int>( ) );

    for( int element : array1 ) {
        cout << element << "\n";
    }

    return EXIT_SUCCESS;
}
