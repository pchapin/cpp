
#include <iostream>
#include <cmath>
#include "Quaternion.hpp"

Quaternion::Quaternion( double a, double b, double c, double d )
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}


void Quaternion::operator+=( const Quaternion &other )
{
    a += other.a;
    b += other.b;
    c += other.c;
    d += other.d;
}


void Quaternion::operator-=( const Quaternion &other )
{
    a -= other.a;
    b -= other.b;
    c -= other.c;
    d -= other.d;
}


void Quaternion::operator*=( const Quaternion &other )
{
    double new_a = a*other.a - b*other.b - c*other.c - d*other.d;
    double new_b = a*other.b + b*other.a + c*other.d - d*other.c;
    double new_c = a*other.c - b*other.d + c*other.a + d*other.b;
    double new_d = a*other.d + b*other.c - c*other.b + d*other.a;

    a = new_a;
    b = new_b;
    c = new_c;
    d = new_d;
}


void Quaternion::operator*=( double scalar )
{
    a *= scalar;
    b *= scalar;
    c *= scalar;
    d *= scalar;
}


Quaternion Quaternion::conj( ) const
{
    Quaternion result( a, -b, -c, -d );
    return result;
}


double Quaternion::norm( ) const
{
    return std::sqrt( a*a + b*b + c*c + d*d );
}


Quaternion left_division( const Quaternion &left, const Quaternion &right)
{
    double norm_of_right = right.norm( );
    Quaternion inverse_of_right = right.conj( ) * (1.0 / (norm_of_right * norm_of_right));
    return inverse_of_right * left;
}


Quaternion right_division( const Quaternion &left, const Quaternion &right)
{
    double norm_of_right = right.norm( );
    Quaternion inverse_of_right = right.conj( ) * (1.0 / (norm_of_right * norm_of_right));
    return left * inverse_of_right;
}


std::ostream &operator<<( std::ostream &output, const Quaternion &right )
{
    output << "(";
    output << right.get_a( ) << ", ";
    output << right.get_b( ) << ", ";
    output << right.get_c( ) << ", ";
    output << right.get_d( ) << ")";
    return output;
}
