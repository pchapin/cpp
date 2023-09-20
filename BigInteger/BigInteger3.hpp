/*! \file   BigInteger3.hpp
 *  \brief  A "third generation" definition of an extended precision integer class.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 *
 * In this version of the class, a move constructor and move assignment operator are provided.
 * The representation is also changed to use base 2**32 digits. This improves performance in
 * both space and time, causing this class to become useful for serious applications.
 */

#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP

#include <cstdint>   // For the exact width types.
#include <iosfwd>
#include <string>

namespace vtsu {

    class BigInteger {

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

        BigInteger( );                                    // Default constructor.
        BigInteger( const BigInteger &other );            // Copy constructor.
        BigInteger &operator=( const BigInteger &other ); // Copy assignment operator.
        BigInteger( BigInteger &&other );                 // Move constructor.
        BigInteger &operator=( BigInteger &&other );      // Move assignment operator.
       ~BigInteger( );                                    // Destructor.

        BigInteger( unsigned long value );

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

        // Operator methods for supporting the usual arithmetic operations.
        //
        // These methods take 'right' by reference to avoid copying large objects. It is a
        // reference to const since the operations do not attempt to modify their right
        // operands. These methods return a reference to 'this' so that they can be chained.
        BigInteger &operator+=( const BigInteger &right );
        BigInteger &operator*=( const BigInteger &right );

        //! Conversion operator to convert BigInteger to unsigned long.
        /*!
         * \throws std::overflow_error if the BigInteger is too large to fit in an unsigned long.
         */
        operator unsigned long( );

    private:
        // This form of `using` creates a type alias. It is the modern C++ way of doing C's
        // typedef. Because these declarations are in the private section of the class, these
        // types cannot be used by client code. This is keeping with the principle of least
        // visibility.
        using storage_type = std::uint32_t;
        using compute_type = std::uint64_t;

        // INVARIANT: If the represented value is zero, `digit_count` is zero and `digits` is
        // the null pointer. Otherwise, `digits` points at an array of size `digit_count`
        // containing the base 2**32 digits of the represented value. The array element at position
        // 0 is the least significant digit of the value. Leading zero digits are never stored.
        storage_type *digits;
        unsigned      digit_count;

        void expand( );      // Expands the object to hold an additional digit.
        void shift_left( );  // Moves all digits to the left one position (except the last).
    };


    inline BigInteger operator+( const BigInteger &left, const BigInteger &right )
    {
        BigInteger temp{ left };
        temp += right;
        return temp;
    }

}


#endif
