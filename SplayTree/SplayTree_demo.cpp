/*! \file   Matrix.hpp
 *  \brief  A program that demonstrates SplayTrees.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include "SplayTree.hpp"

using namespace std;

void simple_constructor_check( )
{
    spica::SplayTree<int> tree1;
}


void initializer_list_constructor_check( )
{
}


int main( )
{
    simple_constructor_check( );
    initializer_list_constructor_check( );
    return EXIT_SUCCESS;
}
