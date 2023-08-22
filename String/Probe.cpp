/*! \file   Probe.cpp
 *  \brief  A class that makes visible the action of the various special methods.
 *  \author Peter C. Chapin <PChapin@vtc.vsc.edu>
 *
 * This file contains an implementation of the Probe class. This version is not very useful for
 * real programs because it just spits out messages onto the standard output device. However,
 * one can imagine a production version of this class that logs messages to a file (or that has
 * options regarding message disposition). Probe objects could be attached to objects either by
 * class membership, in cases where a new class is being defined, or by multiple inheritance in
 * cases where an existing class must be used. Could a useful debugging facility be created from
 * this? Perhaps.
 */

#include <iostream>
#include "Probe.hpp"

static int master_ID = 0;

Probe::Probe( )
{
    ID_number   = ++master_ID;
    std::cout << "Default constructor: ID = " << ID_number << "\n";
}

Probe::Probe( const Probe &existing )
{
    ID_number = ++master_ID;
    std::cout << "Copy constructor: ID = "
              << ID_number
              << ". Copying object "
              << existing.ID_number << "\n";
}

Probe &Probe::operator=( const Probe &other )
{
    std::cout << "Assigning from " << other.ID_number << " to " << ID_number << "\n";
    return *this;
}

Probe::~Probe( )
{
    std::cout << "Destructor: " << ID_number << "\n";
}


Probe::Probe( Probe &&existing )
{
    // Move the value from existing into 'this' object.
    ID_number = existing.ID_number;
    existing.ID_number = 0;
    std::cout << "Move constructor: Moving from ID = " << ID_number << "\n";
}


Probe &Probe::operator=( Probe &&other )
{
    // Move the value from other into 'this object.
    ID_number = other.ID_number;
    other.ID_number = 0;
    std::cout << "Move assignment from ID = " << ID_number << "\n";
    return *this;
}
