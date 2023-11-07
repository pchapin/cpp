/*! \file   Matrix.hpp
 *  \brief  A program that demonstrates SplayTrees.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <vector>
#include "SplayTree.hpp"

namespace {

    void simple_constructor_check( )
    {
        std::cout << "Simple constructor check" << std::endl;

        spica::SplayTree<int> tree1;
        tree1.check_structure( );
    }

    void initializer_list_constructor_check( )
    {
        std::cout << "Initializer list constructor check" << std::endl;

        spica::SplayTree<int> tree1{ 5, 3, 7, 4, 6, 2, 8 };
        tree1.check_structure( );
    }

    // This helper function displays information about a failed dump check and then exits.
    void verify_dump(
        const spica::SplayTree<int> &tree,  // The tree to dump.
        int step,                           // The step number of the test.
        const spica::SplayTree<int>::DumpResult &expected_dump )
    {
        spica::SplayTree<int>::DumpResult result = tree.dump( );
        if( result != expected_dump ) {
            std::cout << "*** Dump result mismatch at step " << step << ": " << std::endl;
            std::cout << "  Expected:" << std::endl;
            std::cout << "    ";
            for( const auto &dump_item : expected_dump ) {
                std::cout << "{ " << dump_item.depth << ", " << dump_item.data << " }, ";
            }
            std::cout << std::endl;
            std::cout << "  Got:" << std::endl;
            std::cout << "    ";
            for( const auto &dump_item : result ) {
                std::cout << "{ " << dump_item.depth << ", " << dump_item.data << " }, ";
            }
            std::cout << std::endl;
            std::exit( EXIT_FAILURE );
        }
    }

    void insert_check( )
    {
        std::cout << "Insert check" << std::endl;

        // This test only exercises 5 of 6 possible reconfigurations. Also, not all possible
        // arrangements of non-null subtrees are checked.
        //
        std::vector<int> test_data = { 5, 3, 7, 4, 6, 2, 8 };
        std::vector<spica::SplayTree<int>::DumpResult> expected_dump_results = {
            { { 0, 5 } },
            { { 0, 3 }, { 1, 5 } },
            { { 2, 3 }, { 1, 5 }, { 0, 7 } },
            { { 1, 3 }, { 0, 4 }, { 2, 5 }, { 1, 7 } },
            { { 2, 3 }, { 1, 4 }, { 2, 5 }, { 0, 6 }, { 1, 7 } },
            { { 0, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }, { 1, 6 }, { 2, 7 } },
            { { 1, 2 }, { 4, 3 }, { 5, 4 }, { 6, 5 }, { 3, 6 }, { 2, 7 }, { 0, 8 } }
        };

        spica::SplayTree<int> tree1;
        for( std::vector<int>::size_type i = 0; i < test_data.size( ); ++i ) {
            tree1.insert( test_data[i] );
            tree1.check_structure( );
            verify_dump( tree1, i, expected_dump_results[i] );
        }
    }

    void find_check( )
    {
        std::cout << "Find check" << std::endl;

        // Note that this data contains a duplicate value.
        std::vector<int> test_data = { 4, 6, 3, 1, 4, 2, 8, 5 };
        std::vector<int> find_data = { 3, 3, 6 };
        std::vector<spica::SplayTree<int>::DumpResult> expected_dump_results = {
            { { 2, 1 }, { 1, 2 }, { 0, 3 }, { 2, 4 }, { 1, 5 }, { 3, 6 }, { 2, 8 } },
            { { 2, 1 }, { 1, 2 }, { 0, 3 }, { 2, 4 }, { 1, 5 }, { 3, 6 }, { 2, 8 } },
            { { 3, 1 }, { 2, 2 }, { 1, 3 }, { 3, 4 }, { 2, 5 }, { 0, 6 }, { 1, 8 } }
        };
        spica::SplayTree<int> tree1;

        // Populate the tree.
        for( int test_item : test_data ) {
            tree1.insert( test_item );
        }

        // Look for things.
        for( std::vector<int>::size_type i = 0; i < find_data.size( ); ++i ) {
            auto find_result = tree1.find( find_data[i] );
            if( *find_result != find_data[i] ) {
                std::cout << "*** Find failed at step " << i << ":" << std::endl;
                std::cout << "  Expected: " << find_data[i] << std::endl;
                std::cout << "  Got     : " << *find_result << std::endl;
                std::exit( EXIT_FAILURE );
            }
            tree1.check_structure( );
            verify_dump( tree1, i, expected_dump_results[i] );
        }

        // Try to find a non-existant item.
        auto find_result = tree1.find( 7 );
        if( find_result != tree1.end( ) ) {
            std::cout << "*** Find failed to return end( ) for non-existant item" << std::endl;
            std::exit( EXIT_FAILURE );
        }
    }

    void erase_check( )
    {
    }

    void iterator_check( )
    {
        std::cout << "Iterator check" << std::endl;

        std::vector<int> test_data = { 4, 6, 3, 1, 4, 2, 8, 5, 7 };
        std::vector<int> result;
        std::vector<int> expected_result = { 1, 2, 3, 4, 5, 6, 7, 8 };
        spica::SplayTree<int> tree1;

        // Populate the tree.
        for( int test_item : test_data ) {
            tree1.insert( test_item );
        }

        // This exercises the begin, end, and the iterator increment operator.
        for( int item : tree1 ) {
            result.push_back( item );
        }
        if( result != expected_result ) {
            std::cout << "*** Iterator check failed" << std::endl;
            std::exit( EXIT_FAILURE );
        }

        // TODO: Exercise the iterator decrement operator.
    }

}

int main( )
{
    simple_constructor_check( );
    initializer_list_constructor_check( );
    insert_check( );
    find_check( );
    erase_check( );
    iterator_check( );
    return EXIT_SUCCESS;
}
