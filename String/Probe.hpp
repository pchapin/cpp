/*! \file   Probe.hpp
 *  \brief  A class that makes visible the action of the various special methods.
 *  \author Peter C. Chapin <PChapin@vtc.vsc.edu>
 *
 * This file contains a class that does nothing other than print messages whenever anything
 * interesting happens to one of its objects. It is (hopefully) a useful learning aid. It may
 * have potential as a debugging aid as well.
 */

#ifndef PROBE_HPP
#define PROBE_HPP

class Probe {
public:
    // C++ 1998...
    Probe( );                           // Default constructor.
    Probe( const Probe & );             // Copy constructor.
    Probe &operator=( const Probe & );  // Copy assignment operator.
   ~Probe( );                           // Destructor.

    // C++ 2011... using rvalue references.
    Probe( Probe && );                  // Move constructor.
    Probe &operator=( Probe && );       // Move assignment operator.

private:
    int ID_number;
};

#endif
