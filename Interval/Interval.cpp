/*! \file   Interval.cpp
 *  \brief  A class for representing floating point intervals
 *  \author Peter C. Chapin <pchapin@vtc.edu>
 */

#include <iostream>
#include "Interval.hpp"

namespace vtc {

    // Member Functions
    // ================
    
    Interval &Interval::operator+=( const Interval &other )
    {
        lower_bound += other.lower_bound;
        upper_bound += other.upper_bound;
        return *this;
    }


    Interval &Interval::operator-=( const Interval &other )
    {
        lower_bound -= other.lower_bound;
        upper_bound -= other.upper_bound;
        return *this;
    }


    Interval &Interval::operator*=( const Interval &other )
    {
        return *this;
    }


    Interval &Interval::operator/=( const Interval &other )
    {
        return *this;
    }


    // Friend Functions
    //=================
    
    std::ostream &operator<<( std::ostream &os, const Interval &value )
    {
        os << "[" << value.lower_bound << ", " << value.upper_bound << "]";
        return os;
    }


    std::istream &operator>>( std::istream &is, Interval &value )
    {
        double lower, upper;
        char   dummy;

        is >> dummy >> lower >> dummy >> upper >> dummy;
        Interval new_value( lower, upper );
        value = new_value;

        return is;
    }


    bool operator==( const Interval &left, const Interval &right )
    {
        double left_midpoint = ( left.upper_bound - left.lower_bound ) / 2.0;
        double right_midpoint = ( right.upper_bound - right.lower_bound ) / 2.0;
        return left_midpoint == right_midpoint;
    }


    bool operator<( const Interval &left, const Interval &right )
    {
        double left_midpoint = ( left.upper_bound - left.lower_bound ) / 2.0;
        double right_midpoint = ( right.upper_bound - right.lower_bound ) / 2.0;
        return left_midpoint < right_midpoint;
    }

}