/*! \file   Animal_demo.cpp
 *  \brief  A program to demonstrate the use of the Animal hierarchy.
 *  \author Peter C. Chapin <pchapin@vtc.edu>
 */

#include <cstdlib>
#include <iostream>
#include <vector>
#include "Animal.hpp"

using namespace std;

// Dispatching only happens through pointers or references. This function returns a vector of
// pointers to dynamically allocated Animals of various kinds. This collection of animals forms
// the "world" in which the simulation occurs (we'd also need some notion of map, but that is
// not discussed in this example).
//
vector<Animal *> initialize( )
{
    vector<Animal *> animals;

    // Note the use of initializer lists to create literal vectors.
    animals.push_back( new Tiger( 0, { 1500.0, 750.0, 0.0 } ) );
    animals.push_back( new Tiger( 1, { 1500.0, 744.0, 0.0 } ) );
    animals.push_back( new Human( 2, { 1497.0, 747.0, 5.0 } ) );

    return animals;
}

int main( )
{
    int return_code = EXIT_SUCCESS;
    vector<Animal *> zoo = initialize( );

    // Run the simulation. Call the time_step method on all the animals. The precise
    // implementation depends on the actual type of the object pointed at by animal. It might
    // be a Tiger or a Human, but we don't need to know that here.
    //
    try {
        for( int steps = 0; steps < 10000; ++steps ) {
            for( auto animal : zoo ) {
                animal->time_step( );
            }
        }
    }
    catch( const char *message ) {
        cerr << "Unhandled exception reached main: " << message << endl;
        return_code = EXIT_FAILURE;
    }
    catch( ... ) {
        cerr << "Unknown exception reached main!" << endl;
    }

    return return_code;
}
