/*! \file   BigInteger2.hpp
 *  \brief  A "second generation" definition of an extended precision integer class.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 *
 * This version of the BigInteger class uses dynamically allocated memory to manage a variable
 * number of digits. To manage the dynamic memory resource, it is necessary to include a copy
 * constructor, a copy assignment operator, and a destructor.
 */

#ifndef BIGINTEGER_HPP
#define BIGINTEGER_HPP

// The header iosfwd contains "forward declarations" of the various iostream classes. Processing
// this header is more efficient than the full iostreams header and so it is better to use in
// other header files. However, the forward declarations only allow you to declare references
// (or pointers) to the stream classes.
#include <iosfwd>
#include <stdexcept>
#include <string>

namespace vtsu {

    class BigInteger {

        // This free function is a friend so it can access the private members directly.
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

        //! Conversion operator to convert BigInteger to unsigned long.
        /*!
         * \throws std::overflow_error if the BigInteger is too large to fit in an unsigned long.
         */
       operator unsigned long( );

    private:
        // INVARIANT: If the represented value is zero, `digit_count` is zero and `digits` is
        // the null pointer. Otherwise `digits` points at an array of size `digit_count`
        // containing the base 10 digits of the represented value. The array element at position
        // 0 is the least significant digit of the value. Leading zero digits are never stored.

        // The type unsigned short only consumes 16 bits of memory and is more memory efficient
        // than the type int (or unsigned int) would be. Further improvements are possible. See
        // BigInteger3.hpp for one approach.
        unsigned short *digits;
        unsigned        digit_count;   // The digit_count can never be negative.

        void expand( );      // Expands the object to hold an additional digit.
        void shift_left( );  // Moves all digits to the left one position (except the last).
    };


    inline BigInteger operator+( const BigInteger &left, const BigInteger &right )
    {
        BigInteger temp{ left };  // Uses the user-defined copy constructor.
        temp += right;
        return temp;
    }

}


#endif
