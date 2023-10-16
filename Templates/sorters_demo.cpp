
#include <algorithm>
#include <cstdlib>
#include <forward_list>
#include <functional>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "sorters.hpp"

using namespace std;

// There are various ways one can define comparison objects. Because the compiler will
// specialize the `bubble_sort_4` template for any comparison type, there is a lot of
// flexibility. Here are some examples.

// An ordinary function will work. The name of this function, `my_ordering` is taken to have
// type `bool (*)(int, int)` (that is, "pointer to function taking two ints and returning
// bool"). Since it allows for the application of `()` the name of this function will serve as a
// comparison object for the `bubble_sort_4` template. The type `Comparison` in the template
// will be specialized as `bool (*)(int, int)`.
//
bool my_ordering( int x, int y )
{
    return x > y;  // `x` "comes before" `y` if `x` is greater than `y`.
}

// Another approach is to create a structure with an overloaded `operator()`. That operator
// could be defined inline (if it is simple) for better performance. Here we define it outside
// the structure for clarity. When calling `bubble_sort_4` with an object of type
// `MyOtherOrdering` the type `Comparison` in the template will be specialized as
// `MyOtherOrdering`.
//
struct MyOtherOrdering {
    bool operator()( int x, int y );
};


bool MyOtherOrdering::operator()( int x, int y )
{
    bool xIsEven = (x % 2) == 0;
    bool yIsEven = (y % 2) == 0;

    // All even numbers come before any odd numbers. Within the even numbers the sort order is
    // ascending. Within the odd numbers the sort order is descending.

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

// This is what `std::less<int>` looks like.
struct my_less {
    inline bool operator()( int x, int y ) { return x < y; }
};


int main( )
{
    // Let's create a comparison object here (which we could reuse, etc., if we wanted).
    MyOtherOrdering strange_order;
    
    // A couple of different array types:
    int array1[] = { 6, 1, 4, 7, 3, 9 };
    std::string array2[] = { "hello", "world", "zebra", "apple", "fizzle", "sticks" };

    // From the STL:
    std::vector<int> my_vector = { 6, 1, 4, 7, 3, 9 };
    std::list<int> my_list = { 6, 1, 4, 7, 3, 9 };
    std::forward_list<int> my_forward_list = { 6, 1, 4, 7, 3, 9 };

    // Sort them all and print them out. The compiler creates a fresh specialization of the
    // `bubble_sort` template for each data type required. Since both ints and strings have a
    // suitable `operator<` defined, the specialization of `bubble_sort` succeeds in every case.
    // Notice that the various library containers also have suitable iterator types defined (and
    // all are at least as powerful as forward iterators), so we can sort containers of various
    // kinds.

    cout << "\nSorting array1..." << endl;
    // vtsu::bubble_sort( array1, array1 + 6 );
    // C++ 2011 and beyond provide std::begin and std::end as an alternative to the above. They
    // allow you to get the bounds on a container in a way that unifies the STL containers and
    // ordinary arrays.
    vtsu::bubble_sort( begin( array1 ), end( array1 ) );

    for( int element : array1 ) {
        cout << element << " ";
    }
    cout << endl;

    cout << "\nSorting array1 in descending order..." << endl;
    // vtsu::bubble_sort( array1, array1 + 6, my_ordering );
    vtsu::bubble_sort( begin( array1 ), end( array1 ), my_ordering );
    // One could also use `std::greater<int>{ }` here.

    for( int element : array1 ) {
        cout << element << " ";
    }
    cout << endl;

    cout << "\nSorting array1 in a strange order..." << endl;
    // vtsu::bubble_sort( array1, array1 + 6, strange_order );
    vtsu::bubble_sort( begin( array1 ), end( array1 ), strange_order );

    for( int element : array1 ) {
        cout << element << " ";
    }
    cout << endl;

    cout << "\nSorting array2 (an array of strings)..." << endl;
    // vtsu::bubble_sort( array2, array2 + 4 );
    vtsu::bubble_sort( begin( array2 ), end( array2 ) );

    for( const string &element : array2 ) {
        cout << element << " ";
    }
    cout << endl;

    cout << "\nSorting my_vector..." << endl;
    // vtsu::bubble_sort( my_vector.begin(), my_vector.end() );
    vtsu::bubble_sort( begin( my_vector ), end( my_vector ) );

    for( int element : my_vector ) {
        cout << element << " ";
    }
    cout << endl;

    cout << "\nSorting my_list..." << endl;
    // vtsu::bubble_sort( my_list.begin(), my_list.end() );
    vtsu::bubble_sort( begin( my_list ), end( my_list ) );

    for( int element : my_list ) {
        cout << element << " ";
    }
    cout << endl;

    // Forward lists are interesting because they *only* provide forward iterators. However, the
    // bubble sort algorithm is fine with that. Most sorting algorithms need more powerful
    // iterators, and thus can't be used with forward lists. For example, the `std::sort`
    // template requires random access iterators and thus can only work on arrays, vectors, and
    // deques (or any user-defined container that provides random access iterators).

    cout << "\nSorting my_forward_list..." << endl;
    // vtsu::bubble_sort( my_forward_list.begin(), my_forward_list.end() );
    vtsu::bubble_sort( begin( my_forward_list ), end( my_forward_list ) );

    for( int element : my_forward_list ) {
        cout << element << " ";
    }
    cout << endl;

    return EXIT_SUCCESS;
}
