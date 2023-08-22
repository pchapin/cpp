/*! \file   BigInteger1.hpp
 *  \brief  A "first generation" definition of an extended precision integer class.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP

#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace vtsu {

    //! This class supports very large *unsigned* integers.
    /*!
     * This class supports unsigned integers with at most 128 decimal digits. The usual
     * arithmetic operations are supported. The exception `std::overflow_error` is thrown if an
     * arithmetic operation results in a value that is too large to be represented. The
     * exception `std::underflow_error` is thrown if an arithmetic operation results in a value
     * that is too small to be represented (i.e., negative).
     * 
     * Implicit conversions from `unsigned long` and `std::string` are supported. Explicit
     * conversions to `unsigned long` are supported.
     */
    class BigInteger {

        // Declaration of a non-method that can access the private section of BigInteger.
        friend std::ostream &operator<<( std::ostream &os, const BigInteger &bi );

    public:
        //! Exception thrown when an invalid format is used to construct a BigInteger.
        class InvalidFormat : std::runtime_error {
        public:
            InvalidFormat( const std::string &message ) : std::runtime_error( message ) { }
        };

        //! Exception thrown when an operation is not implemented.
        class NotImplemented : std::logic_error {
        public:
            NotImplemented( const std::string &message ) : std::logic_error( message ) { }
        };

        // Default constructor. Creates a BigInteger with the value 0.
        BigInteger( );

        // Copy constructor and copy assignment operator are automatically generated.
        // BigInteger( const BigInteger & );
        // BigInteger &operator=( const BigInteger & );

        //! Constructs a BigInteger from an unsigned long value.
        BigInteger( unsigned long value );

        //! Constructs a BigInteger from a string of decimal digits.
        /*!
         * \param raw_digits The string of decimal digits. The digits are assumed to be in
         *  big-endian order. That is, the most significant digit is first and the least
         *  significant digit is last. No characters other than digits are allowed.
         * 
         * \throws InvalidFormat if the string contains any non-digit characters.
         * \throws std::overflow_error if the string contains a value that is too large to be
         * represented by a BigInteger.
         */
        BigInteger( const std::string &raw_digits );
        
        //! Returns the number of decimal digits in the the number.
        /*!
         * Leading zero digits are not included in the count. The value 0 has zero digits.
         */
        int number_of_digits( ) const;

        // Operator methods for supporting the usual arithmetic operations.
        //
        // These methods take 'right' by reference to avoid copying large objects. It is a
        // reference to const since the operations do not attempt to modify their right
        // operands. These methods return a reference to 'this' so that they can be chained.
        BigInteger &operator+=( const BigInteger &right );
        BigInteger &operator-=( const BigInteger &right );
        BigInteger &operator*=( const BigInteger &right );
        BigInteger &operator/=( const BigInteger &right );
        BigInteger &operator%=( const BigInteger &right );

        //! Conversion operator to convert BigInteger to unsigned long.
        /*!
         * \throws std::overflow_error if the BigInteger is too large to fit in an unsigned long.
         */
        operator unsigned long( ) const;

    private:
        // Static members exist even if you never create any class instances. Static constants
        // can be initialized inside the class definition. They are constant expressions known
        // to the compiler and can be used as such.
        static const size_t maximum_size = 128;

        // Each element of the digits array is a base 10 digit. The digits are stored in this
        // array in little-endian order. That is, the least significant digit is first and the
        // most significant digit is last. The digits array is always completely filled. If
        // there are fewer than maximum_size digits in the number, the unused digits are
        // set to zero.
        //
        // TODO: Fix this memory inefficiency.
        // Here 32 bits are used to hold less than 4 bits of information. Better representations
        // are possible (see BigInteger2.hpp).
        int digits[maximum_size];
    };


    // These functions return a BigInteger by value (not reference) to avoid returning a
    // reference to a local variable that will be deallocated with the function returns. Uses of
    // these operators are, in effect, replaced with the temporary object that is returned by
    // them.

    inline BigInteger operator+( const BigInteger &left, const BigInteger &right )
    {
        BigInteger temp{ left };  // Uses the generated copy constructor.
        temp += right;
        return temp;
    }

    inline BigInteger operator-( const BigInteger &left, const BigInteger &right )
    {
        BigInteger temp{ left };  // Uses the generated copy constructor.
        temp -= right;
        return temp;
    }

    inline BigInteger operator*( const BigInteger &left, const BigInteger &right )
    {
        BigInteger temp{ left };  // Uses the generated copy constructor.
        temp *= right;
        return temp;
    }

    inline BigInteger operator/( const BigInteger &left, const BigInteger &right )
    {
        BigInteger temp{ left };  // Uses the generated copy constructor.
        temp /= right;
        return temp;
    }

    inline BigInteger operator%( const BigInteger &left, const BigInteger &right )
    {
        BigInteger temp{ left };  // Uses the generated copy constructor.
        temp %= right;
        return temp;
    }

}

#endif
