/*! \file   references.cpp
 *  \brief  A simple program that illustrates C++ references.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 *
 * This program demonstrates various versions of swap to illustrate how references work.
 */

#include <cstdlib>
#include <iostream>

using namespace std;


// This version does not work as intended. The parameters `x` and `y` are COPIES of the
// arguments provided at the call site. While this function does swap the parameters, that has
// no effect on the caller's arguments. This is the same behavior as in C.
void swap( int x, int y )
{
    int temp = x;
    x = y;
    y = temp;
}


// This version using pointers does work, but the caller must send in the address of the
// integers to be swapped. A call might look like: `swap( &a, &b )`. This is how the function
// would be written in C, but it works for C++ as well due to C++'s C compatibility. Notice that
// the name of this function is also `swap` but that is fine in C++ since the parameter types
// are "sufficiently" different than for the `swap` above. C++ allows function overloading based
// on parameters.
void swap( int *x, int *y )
{
	int temp = *x;
	*x = *y;
	*y = temp;
}


// This version uses C++ references. Here `x` and `y` refer to the arguments and are not copies
// of the arguments. However, they can be treated as if they were the arguments without using
// pointer indirection. They are, in effect, aliases of the arguments. In this case I can't just
// call this function 'swap' because it would be ambiguous with the earlier `swap` that takes
// plain integer parameters.
void swap_using_references( int &x, int &y )
{
    int temp = x;
    x = y;
    y = temp;
}


// Using references a function can modify the argument (which isn't possible in C without
// using explicit pointers. Thus "out" parameters are more naturally expressed.
void initialize_int( int &x )
{
    x = 0;
}


int main( )
{
    int a = 42;
    int b = 84;

    // The swapping works correctly. The values of `a` and `b` are exchanged.
    cout << "The original values are: a = " << a << ", b = " << b << endl;
    swap_using_references( a, b );
    cout << "The values after swapping are: a = " << a << ", b = " << b << endl;

    // This sets `a` to zero.
    initialize_int( a );

    int x = 42;
    int &r = x;  // The reference `r` is bound to `x` and thus is an alias for `x`.
                 // This is an unusual way to use references.

    // This prints the value of `x` since `r` refers to `x`.
    cout << "The value of r is: " << r << endl;

    return EXIT_SUCCESS;
}
