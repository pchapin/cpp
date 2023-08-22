/*! \file   Rational.hpp
 *  \brief  A template for managing rational numbers.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <concepts>
#include <iostream>

namespace vtsu {

    template<typename UIntType>
    concept Rationalizable = std::unsigned_integral<UIntType>;

    //! A template for managing rational numbers.
    /*!
     * This class template represents rational numbers as a numerator and denominator. Only
     * unsigned rationals are supported.
     * 
     * Instances of this class are "semi-immutable" meaning that they cannot be modified after
     * construction *except* by the input `operator>>` which is permitted to overwrite an existing
     * value. The assignment operator is deleted, but copy construction is allowed.  The default
     * constructor also exists, although it is only useful for variables that you intend to read
     * from input later.
     * 
     * \tparam UIntType The type used to represent the numerator and denominator. This type must be
     * an unsigned integer type.
     */
    template<typename UIntType>
        requires Rationalizable<UIntType>
    class Rational {

        // Because Rational is a template with many possible specializations, the input and output
        // operators also need to be templates so they can be instantiated as needed for each
        // specialization of Rational. The declarations below state that every specialization of the
        // two I/O operators is a friend of every specialization of Rational.
        //
        // For example, `operator>>` specialized for type T = unsigned long is a friend of Rational
        // specialized for type UIntType = unsigned. This seems a bit weird since the two template
        // parameter types in the example are different. In practice, it is not a problem. We only
        // want to be sure that `operator>>` specialized for type T = unsigned is a friend of
        // Rational specialized for type UIntType = unsigned, and so forth.

        // Operator>> needs to be a friend because the only way to set a rational value outside of a
        // constructor is via the private `set` method. Operator<< is also a friend just for
        // symmetry.

        template<typename T>
        friend std::istream &operator>>( std::istream &is, Rational<T> &rat );
    
        template<typename T>
        friend std::ostream &operator<<( std::ostream &os, const Rational<T> &rat );

    public:

        // Because this class is semi-immutable, the only way to set the value of a default-
        // constructed Rational is via `operator>>`.
        Rational( )
            : numerator{ 0 }, denominator{ 1 } { }

        // Constructor with a default value for the second parameter as a convenience. Notice that
        // this constructor can be used as an implicit conversion from UIntType to
        // Rational<UIntType>.
        //
        // TODO: Check for division by zero.
        Rational( UIntType n, UIntType d = 1 ) : numerator{ n }, denominator{ d }
            { reduce( ); }

        // Deleted assignment operator.
        Rational &operator=( const Rational & ) = delete;

        // Accessor methods.
        UIntType get_numerator( ) const
            { return numerator; }

        UIntType get_denominator( ) const
            { return denominator; }

    private:
        UIntType numerator;
        UIntType denominator;

        void reduce( );
        void set( const UIntType &n, const UIntType &d )
            { numerator = n; denominator = d; reduce( ); }
    };


    // Arithmetic Operators
    // --------------------

    template<typename UIntType>
    Rational<UIntType> operator+( const Rational<UIntType> &left, const Rational<UIntType> &right )
    {
        // TODO: Deal with overflow problems!
        UIntType common_denominator = left.get_denominator( ) * right.get_denominator( );
        UIntType new_numerator =
            left.get_numerator( )  * right.get_denominator( ) +
            right.get_numerator( ) * left.get_denominator( );
        UIntType new_denominator = common_denominator;

        return Rational{ new_numerator, new_denominator };
    }

    template<typename UIntType>
    Rational<UIntType> operator-( const Rational<UIntType> &left, const Rational<UIntType> &right )
    {
        // TODO: Deal with overflow problems!
        UIntType common_denominator = left.get_denominator( ) * right.get_denominator( );
        UIntType new_numerator =
            left.get_numerator( )  * right.get_denominator( ) -
            right.get_numerator( ) * left.get_denominator( );
        UIntType new_denominator = common_denominator;
    
        return Rational{ new_numerator, new_denominator };
    }

    template<typename UIntType>
    Rational<UIntType> operator*( const Rational<UIntType> &left, const Rational<UIntType> &right )
    {
        // TODO: Deal with overflow problems!
        UIntType new_numerator = left.get_numerator( ) * right.get_numerator( );
        UIntType new_denominator = left.get_denominator( ) * right.get_denominator( );

        return Rational{ new_numerator, new_denominator };
    }

    // TODO: Check for division by zero.
    template<typename UIntType>
    Rational<UIntType> operator/( const Rational<UIntType> &left, const Rational<UIntType> &right )
    {
        // TODO: Deal with overflow problems!
        UIntType new_numerator = left.get_numerator( ) * right.get_denominator( );
        UIntType new_denominator = left.get_denominator( ) * right.get_numerator( );

        return Rational{ new_numerator, new_denominator };
    }


    // Reduction
    // ---------

    // Find the greatest common divisor of a and b using Euclid's algorithm. This function only
    // works if a and b are positive. Notice that `a` and `b` are being passed by value. This is
    // because they need to be modified without changing the arguments.
    template<typename UIntType>
        requires std::unsigned_integral<UIntType>
    UIntType gcd( UIntType a, UIntType b )
    {
        while( a != b ) {
            if ( a > b )
                a -= b;
            else
                b -= a;
        }
        return a;
    }

    // This method reduces the rational to lowest terms. Although this method modifies the rational,
    // it can still be part of an immutable class since it is only used during construction and is
    // otherwise private.
    template<typename UIntType>
        requires Rationalizable<UIntType>
    void Rational<UIntType>::reduce( )
    {
        UIntType common_divisor = gcd( numerator, denominator );

        numerator /= common_divisor;
        denominator /= common_divisor;
    }



    // Relational Operators
    // --------------------

    template<typename UIntType>
    auto operator<=>( const Rational<UIntType> &left, const Rational<UIntType> &right )
    {
        return left.get_numerator( ) * right.get_denominator( )
            <=> right.get_numerator( ) * left.get_denominator( );
    }


    // Rational I/O
    // ------------

    template<typename T>
    std::istream &operator>>( std::istream &is, Rational<T> &rat )
    {
        T    numerator;
        T    denominator;
        char dummy;
    
        // TODO: Enforce stricter formatting rules for the input (input validation).
        // Perhaps the RE should be: \d+(/\d+)?
        is >> numerator >> dummy >> denominator;
        rat.set( numerator, denominator );
        return is;
    }

    template<typename T>
    std::ostream &operator<<( std::ostream &os, const Rational<T> &rat )
    {
        // TODO: Honor requested formatting (field width, padding, etc.)
        if( rat.denominator == 1 ) {
            os << rat.numerator;
        }
        else {
            os << rat.numerator << "/" << rat.denominator;
        }
        return os;
    }

}

#endif
