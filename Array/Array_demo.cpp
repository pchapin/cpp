
#include <iostream>
#include <string>
#include <utility>   // Needed for std::rel_ops

#include "ArrayStatic.hpp"
#include "ArrayDynamic.hpp"

struct Example {
    int x, y, z;
};

// Uses of 'default_size' are constant expressions.
const int default_size = 32;

// This function can be evaluated by the compiler if used in an appropriate context.
constexpr int max(int x, int y)
{
    return (x > y) ? x : y;
}


void f( int size )
{
    // It is okay to create an ArrayDynamic using a size that is computed at runtime. Note that
    // two different ArrayDynamic<char> with different sizes are the same type. This is not true
    // for ArrayStatic since the size, being a template parameter, is part of the type. Once
    // consequence of this is that the code for ArrayDynamic must consider (at runtime)
    // different sizes, for example when copying. ArrayStatic's methods don't have to worry
    // about that.
    //
    ArrayDynamic<char> my_arrayDynamic( size );

    // ... but the template argument 'size' must be a constant expression.
    // ArrayStatic<char, size> my_arrayStatic;
}


int main( )
{
    ArrayStatic<char, default_size>   my_array1;
    ArrayStatic<char, default_size>   my_array2;
    ArrayStatic<char, 2*default_size> my_array3;
    ArrayStatic<char, max(2*default_size, 1024)> my_array4;
    
    ArrayStatic<Example, 16> example_array1, example_array2;

    for( std::size_t i = 0; i < default_size; ++i ) {
        my_array1[i] = 'x';
    }

    my_array2 = my_array1;  // OK. Types match, assignment is auto-generated.
//  my_array2 = my_array3;  // Error. Types don't match.
//  my_array3 = my_array4;  // Is this ok? NO! my_array4 has size 1024.

    if( my_array1 == my_array2 ) {  // Really my_array1.operator==( my_array2 )
        std::cout << "Hello ";
    }
    my_array2[0] = 'y';
    if( my_array1 < my_array2 ) {
        std::cout << "World!\n";
    }

    //if( example_array1 == example_array2 ) {
    //    std::cout << "Yeah!\n";
    //}
    example_array2 = example_array1;

    using namespace std::rel_ops;

    // Use operator!= instantiated from the std::rel_ops::operator!= template.
    if( my_array1 != my_array2 ) {
        std::cout << "They are not equal!\n";
    }
    std::cout << std::flush;

    // Off-the-end access throws std::out_of_range exception.
    my_array1.at( default_size ) = 'z';

    return 0;
}
