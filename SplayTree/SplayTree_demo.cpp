/*! \file   Matrix.hpp
 *  \brief  A program that demonstrates SplayTrees.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
#include "SplayTree.hpp"

using namespace std;

void simple_constructor_check( )
{
    spica::SplayTree<int> tree1;
    tree1.check_structure( );
}

void initializer_list_constructor_check( )
{
}

void insert_check( )
{
    std::vector<int> test_data = { 5, 3, 7, 4, 6, 2, 8 };
    vector<spica::SplayTree<int>::DumpResult> expected_dump_results = {
         { { 0, 5 } },
         { { 0, 3 }, { 1, 5 } },
         { { 2, 3 }, { 1, 5 }, { 0, 7 } },
         { { 1, 3 }, { 0, 4 }, { 2, 5 }, { 1, 7 } },
         { { 2, 3 }, { 1, 4 }, { 2, 5 }, { 0, 6 }, { 1, 7 } },
         { { 0, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 1, 6 }, { 2, 7 } },
         { { 1, 2 }, { 4, 3 }, { 5, 4 }, { 6, 5 }, { 3, 6 }, { 2, 7 }, { 0, 8 } }
    };

    spica::SplayTree<int> tree1;
    for( int i = 0; i < test_data.size( ); ++i ) {
        tree1.insert( test_data[i] );
        tree1.check_structure( );

        spica::SplayTree<int>::DumpResult result = tree1.dump( );
        if( result != expected_dump_results[i] ) {
            cout << "Dump result mismatch at step " << i << endl;
            cout << "Expected: " << endl;
            for( const auto &dump_item : expected_dump_results[i] ) {
                cout << "  " << "{ " << dump_item.depth << ", " << dump_item.data << " }" << endl;
            }
            cout << "Got: " << endl;
            for( const auto &dump_item : result ) {
                cout << "  " << "{ " << dump_item.depth << ", " << dump_item.data << " }" << endl;
            }
            exit( EXIT_FAILURE );
        }
    }
}

int main( )
{
    simple_constructor_check( );
    initializer_list_constructor_check( );
    insert_check( );
    return EXIT_SUCCESS;
}
