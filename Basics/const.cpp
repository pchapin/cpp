/*! \file   const.cpp
 *  \brief  A simple program that illustrates some aspects of 'const' in C++.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iostream>

using namespace std;

// This function adds the given value to an accumulator. Since the value being added is not
// modified, it can be treated as a constant. Hence `new_value` has type "pointer to const int."
// However, the object referred to by `accumulator` IS being changed so it cannot be declared as
// a reference to a const int. Note that just because `new_value` MAY point at a constant int
// doesn't mean that it MUST. It is permitted to pass this function a pointer that points at a
// regular (non-const) int. The `const` on the parameter declaration only means that this
// function chooses to treat the object pointed at by `new_value` as a constant... it does not
// mean that object actually is a constant.
void accumulate( int &accumulator, const int *new_value )
{
    accumulator = accumulator + *new_value;
}


int main( )
{
    int acc = 0;                 // Initialize the accumulator.
    int value = 42;              // An ordinary (non-const) int.
    const int const_value = 84;  // A constant int.

    accumulate( acc, &value );   // &value can be treated as a pointer to a const.
    value = 63;                  // Change 'value' (it's not a constant)...
    accumulate( acc, &value );   // ... and add it to the accumulator.
    accumulate( acc, &const_value );  // &const_value is a pointer to a const. That's ok.
    cout << acc << endl;         // The final answer is?
    return EXIT_SUCCESS;
}
