/*! \file   Animal.cpp
 *  \brief  A demonstration class hierarchy.
 *  \author Peter C. Chapin <pchapin@vtc.edu>
 */

#include <iostream>
#include "Animal.hpp"

using namespace std;

// Animal's constructor should probably verify the sanity of the initial_position.
Animal::Animal( int id, vector<double> initial_position, bool sleeping_flag )
{
    this->id         = id;
    this->sleeping   = sleeping_flag;
    this->x_position = initial_position.at( 0 ); // The at() method throws if index out of range.
    this->y_position = initial_position.at( 1 );
    this->z_position = initial_position.at( 2 );
}


// In the simulation program this method simulates the behavior of a tiger during on time step
// (for example, a 10 second interval). The method might want to update the tiger's position
// stored in the protected section of Tiger's base class Animal. However, since 'id' is private
// in Animal, this method would need to use Animal's public interface to access the id.
//
void Tiger::time_step( )
{
    throw "Tiger::time_step not implemented";
    return;
}


void Human::time_step( )
{
    throw "Human::time_step not implemented";
    return;
}


