/*! \file   Interval.hpp
 *  \brief  A class for representing floating point intervals
 *  \author Peter C. Chapin <pchapin@vtc.edu>
 *
 * Instances of this class can be used to represent uncertain values. Instead of storing a
 * single value, they store a range. Computations on Intervals follow standard interval
 * arithmetic.
 */

#ifndef INTERVAL_HPP
#define INTERVAL_HPP

#include <iosfwd>

namespace vtc {

    class Interval {

        friend std::ostream &operator<<( std::ostream &os, const Interval &value );
        friend std::istream &operator>>( std::istream &is, Interval &value );
        friend bool operator==( const Interval &left, const Interval &right );
        friend bool operator< ( const Interval &left, const Interval &right );

    public:
        Interval( double lower, double upper )
        {
            // TODO: Add check to ensure lower <= upper?
            lower_bound = lower; upper_bound = upper;
        }

        Interval &operator+=( const Interval &other );
        Interval &operator-=( const Interval &other );
        Interval &operator*=( const Interval &other );
        Interval &operator/=( const Interval &other );

    private:
        double lower_bound;
        double upper_bound;
    };

    // Inline Free Functions
    // =====================

    inline Interval operator+( const Interval &left, const Interval &right )
    {
        Interval temp( left );
        temp += right;
        return temp;
    }

    inline Interval operator-( const Interval &left, const Interval &right )
    {
        Interval temp( left );
        temp -= right;
        return temp;
    }

    inline Interval operator*( const Interval &left, const Interval &right )
    {
        Interval temp( left );
        temp *= right;
        return temp;
    }

    inline Interval operator/( const Interval &left, const Interval &right )
    {
        Interval temp( left );
        temp /= right;
        return temp;
    }

    inline bool operator!=( const Interval &left, const Interval &right )
    {
        return !( left == right );
    }

    inline bool operator<=( const Interval &left, const Interval &right )
    {
        return left < right || left == right;
    }

    inline bool operator>( const Interval &left, const Interval &right )
    {
        return !( left <= right );
    }

    inline bool operator>=( const Interval &left, const Interval &right )
    {
        return !( left < right );
    }

}

#endif
