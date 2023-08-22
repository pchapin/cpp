/*! \file   BigInteger2.cpp
 *  \brief  A "second generation" definition of an extended precision integer class.
 *  \author Peter C. Chapin <pchapin@vtc.edu>
 */

#include <iostream>
#include <cctype>
#include <cstring>
#include "BigInteger2.hpp"

using namespace std;

namespace vtsu {

    BigInteger::BigInteger( )
    {
        // A BigInteger with no digits is taken to be zero.
        // We will also use the convention that `digits` will be the null pointer in that case.
        digit_count = 0;
        digits = nullptr;
    }


    BigInteger::BigInteger( const BigInteger &other )
    {
        digit_count = other.digit_count;

        // Handle copy construction of zero as a special case.
        if( digit_count == 0 ) {
            digits = nullptr;
        }
        else {
            // Otherwise allocate space for a copy of the digits and then copy them.
            digits = new unsigned short[other.digit_count];
            std::memcpy( digits, other.digits, digit_count * sizeof( unsigned short ) );
        }
    }


    BigInteger &BigInteger::operator=( const BigInteger &other )
    {
        // First, check for self-assignment.
        if( this != &other ) {

            // Next, get rid of the digits array we are currently managing.
            // This is not exception safe.
            // TODO: Fix the exception safety issue!
            delete [] digits;

            // Finally do what is essentially the same logic as the copy constructor. Notice
            // that the copy assignment operator has extra work and so is, in general, slower.
            // In some cases it might make sense to factor the actual copying into a private
            // method and call that private method from both the copy constructor and the copy
            // assignment operator.
            digit_count = other.digit_count;
            if( digit_count == 0 ) {
                digits = nullptr;
            }
            else {
                digits = new unsigned short[other.digit_count];
                std::memcpy( digits, other.digits, digit_count * sizeof( unsigned short ) );
            }
        }
        return *this;
    }


    BigInteger::~BigInteger( )
    {
        delete [] digits;
    }


    BigInteger::BigInteger( unsigned long value )
    {
        // Be sure the number is initialized to zero.
        digit_count = 0;
        digits = nullptr;

        while( value > 0UL ) {
            expand( );
            digits[digit_count - 1] = static_cast<unsigned short>( value % 10UL );
            value = value / 10UL;
        }
    }


    BigInteger::BigInteger( const string &raw_digits )
    {
        // Be sure the number is initialized to zero.
        digit_count = 0;
        digits = nullptr;

        // Check to ensure all characters of the string are digits.
        for_each( raw_digits.begin( ), raw_digits.end( ), [ ]( char c ) {
            if( !isdigit( c ) ) throw InvalidFormat( "Non-digit in BigInteger::BigInteger( const string & )" );
        } );

        // Find the first non-zero digit.
        string::size_type first_non_zero_digit_position = raw_digits.find_first_not_of( '0' );

        // If the string is all zero digits, we're done.
        if( first_non_zero_digit_position == string::npos ) return;

        bool in_number = false;
        for( char digit_character : raw_digits ) {
            if( !in_number && digit_character == '0' ) continue;
 
            in_number = true;
            expand( );
            shift_left( );
            digits[0] = static_cast<unsigned short>( digit_character - '0' );
        }
    }


    BigInteger &BigInteger::operator+=( const BigInteger &right )
    {
        // TODO: Does this code work if we try to add an object to itself?

        // First deal with the case when one (or both) of the numbers are zero. This is needed
        // because zero is represented in a special way.
        if( right.digit_count == 0 ) return *this;
        if( digit_count == 0 ) {
            digit_count = right.digit_count;
            // This check is needed to deal with 0 += 0.
            if( digit_count != 0 ) {
                digits = new unsigned short[digit_count];
                std::memcpy( digits, right.digits, digit_count * sizeof( unsigned short ) );
            }
            return *this;
        }

        // Both numbers are non-zero...

        // How many digits do we have to process?
        const unsigned max_size =
            ( digit_count > right.digit_count ) ? digit_count : right.digit_count;

        unsigned short other_digit;
        int sum;
        int carry = 0;

        // Process all digits...
        for( unsigned digit_index = 0; digit_index < max_size; ++digit_index ) {

            // If I'm out of digits, I need to expand.
            if( digit_index > digit_count - 1 ) expand( );

            // If the other number is out of digits, use zero; otherwise use its digit.
            if( digit_index > right.digit_count - 1 ) {
                other_digit = 0;
            }
            else {
                other_digit = right.digits[digit_index];
            }

            // Do the addition.
            sum = digits[digit_index] + other_digit + carry;
            digits[digit_index] = sum % 10;
            carry = sum / 10;
        }

        // Handle an overall carry if there is one.
        if( carry != 0 ) {
            expand( );
            digits[digit_count - 1] = carry;
        }
        return *this;
    }


    BigInteger::operator unsigned long( )
    {
        unsigned long value = 0;
        int digit_index = digit_count - 1;

        while( digit_index >= 0 ) {
            value = 10UL*value + digits[digit_index];
            digit_index--;
        }
        // TODO: Add overflow check. We should throw an exception.
        return value;
    }


    // This method violates an invariant of the class. In particular, it creates a number with a
    // leading zero. This isn't a problem, however, because this method is private. It is the
    // responsibility of the calling method to reestablish the invariant before returning.
    // Clients of the BigInteger class are not aware of the temporarily invalid state of the
    // object (at least not in a single-threaded program).
    void BigInteger::expand( )
    {
        // Expanding zero entails adding a single digit.
        if( digits == nullptr ) {
            digits = new unsigned short[1];
            digits[0] = 0;
        }
        else {
            // Otherwise allocate a new, slightly larger array and copy all the digits into it.
            // Set the new digit to zero for now. Note that this can get slow for very large
            // numbers of digits. It would be better to expand the array in blocks where the
            // block size increases each time the array is reallocated. That would require
            // keeping track of both the size of the array and the number of "actual" digits it
            // contains.
            unsigned short *new_digits = new unsigned short[digit_count + 1];
            std::memcpy( new_digits, digits, digit_count * sizeof( unsigned short ) );
            new_digits[digit_count] = 0;
            delete [] digits;
            digits = new_digits;
        }
        digit_count++;
    }


    // This method overwrites without warning the most significant digit of the number. It also
    // has undefined behavior if applied to a BigInteger with a value of zero. These problems
    // are not exposed to clients since this is a private method. The other methods of this
    // class need to account for these restrictions, however.
    void BigInteger::shift_left( )
    {
        std::memmove( &digits[1], &digits[0], (digit_count - 1) * sizeof( unsigned short ) );
    }


    ostream &operator<<( ostream &os, const BigInteger &bi )
    {
        // The number zero must be handled as a special case.
        if( bi.digit_count == 0 ) {
            os << '0';
        }
        else {
            // This is a little dangerous. What if the number of digits was greater than the
            // type int could represent? That happens for numbers with more than two billion
            // digits.
            int digit_index = static_cast<int>( bi.digit_count ) - 1;

            // We need digit_index to be int so the test 'digit_index >= 0' can be false.
            while( digit_index >= 0) {
                os << static_cast<char>( bi.digits[digit_index] + '0' );
                digit_index--;
            }
        }
        return os;
    }

}
