
#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include <iosfwd>

class Quaternion {
public:
    // Constructors.
    Quaternion( );
    Quaternion( double a, double b, double c, double d );

    // Accessors.
    double get_a( ) const;
    double get_b( ) const;
    double get_c( ) const;
    double get_d( ) const;

    // Basic mathematical operations.
    void operator+=( const Quaternion &other );
    void operator-=( const Quaternion &other );
    void operator*=( const Quaternion &other );
    void operator*=( double scalar );

    // Various additional operations.
    Quaternion conj( ) const;
    double     norm( ) const;

private:
    double a, b, c, d;
};

// Inline method definitions
// =========================

inline
Quaternion::Quaternion( )
    { a = b = c = d = 0.0; }

inline
double Quaternion::get_a( ) const
    { return a; }

inline
double Quaternion::get_b( ) const
    { return b; }

inline
double Quaternion::get_c( ) const
    { return c; }

inline
double Quaternion::get_d( ) const
    { return d; }


// Free function declarations/definitions
// ======================================

inline
Quaternion operator+( const Quaternion &left, const Quaternion &right )
{
    Quaternion result( left );
    result += right;
    return result;
}


inline
Quaternion operator-( const Quaternion &left, const Quaternion &right )
{
    Quaternion result( left );
    result -= right;
    return result;
}


inline
Quaternion operator*( const Quaternion &left, const Quaternion &right )
{
    Quaternion result( left );
    result *= right;
    return result;
}


inline
Quaternion operator*( double left, const Quaternion &right )
{
    Quaternion result( right );
    result *= left;
    return result;
}


inline
Quaternion operator*( const Quaternion &left, double right )
{
    Quaternion result( left );
    result *= right;
    return result;
}

Quaternion left_division ( const Quaternion &left, const Quaternion &right);
Quaternion right_division( const Quaternion &left, const Quaternion &right);
std::ostream &operator<<( std::ostream &output, const Quaternion &right );

#endif
