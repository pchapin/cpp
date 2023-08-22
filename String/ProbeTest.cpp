/*! \file   main.cpp
 *  \brief  A demonstration program that illustrates how class Probe works.
 *  \author Peter C. Chapin <PChapin@vtc.vsc.edu>
 */

#include <iostream>
#include "Probe.hpp"

Probe global_object;

Probe f( Probe incoming )
{
    Probe result;

    result = incoming;
    return result;
}

int main( )
{
    Probe answer;

    answer = f( answer );
    return 0;
}
