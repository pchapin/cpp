/*! \file   BigInteger3.cpp
 *  \brief  A "third generation" definition of an extended precision integer class.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cctype>
#include <cstring>
#include <iostream>
#include <limits>    // For std::numeric_limits
#include "BigInteger3.hpp"

using namespace std;

namespace vtsu {

    BigInteger::BigInteger( )
    {
        // A BigInteger with no digits is taken to be zero.
        // We will also use the convention that 'digits' will be the null pointer in that case.
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
            digits = new storage_type[other.digit_count];
            std::memcpy( digits, other.digits, digit_count * sizeof( storage_type ) );
        }
    }


    BigInteger &BigInteger::operator=( const BigInteger &other )
    {
        // First, check for self-assignment.
        if( this != &other ) {

            if( other.digit_count == 0 ) {
                delete [] digits;
                digits = nullptr;
                digit_count = other.digit_count;
            }
            else {
                // This is exception safe. Allocate storage *before* deleting our value.
                storage_type *temp = new storage_type[other.digit_count];
                std::memcpy( digits, other.digits, digit_count * sizeof( storage_type ) );
                delete [] digits;
                digits = temp;
                digit_count = other.digit_count;
            }
        }
        return *this;
    }


    // Move Constructor
    // ---------------
    //
    // This method "drains" the other object and transfers its value into 'this' object. Note
    // that it is careful to maintain the destructibility of the other object. This is because
    // even after being moved-from, the compiler will still destroy the "shell" of the other
    // object. The invocation of the destructor on that shell must be well-behaved.
    //
    BigInteger::BigInteger( BigInteger &&other )
    {
        // Move the other value into ourselves.
        digit_count = other.digit_count;
        digits = other.digits;

        // Put the other object into a meaningful, destructible state. In this case the other
        // object is fully functional (it appears to be zero). However, moving from an object
        // need not leave the object functional, only destructible.
        other.digit_count = 0;
        other.digits = nullptr;
    }


    // Move Assignment Operator
    // ------------------------
    //
    // This method has the same relationship to the move constructor as the copy assignment
    // operator has to the copy constructor. In particular, it must remove the value in 'this'
    // object before performing the move.
    //
    BigInteger &BigInteger::operator=( BigInteger &&other )
    {
        // First, check for self-assignment.
        if( this != &other ) {

            // Next, get rid of the digits array we are currently managing. This is exception
            // safe because none of the operations done after this can possibly throw an
            // exception.
            delete [] digits;

            // Move the other value into ourselves.
            digit_count = other.digit_count;
            digits = other.digits;

            // Put the other object into a meaningful, destructible state.
            other.digit_count = 0;
            other.digits = nullptr;
        }
        return *this;
    }


    BigInteger::~BigInteger( )
    {
        delete [] digits;
    }


    BigInteger::BigInteger( unsigned long value )
    {
        static_assert( numeric_limits<unsigned long>::max( ) > numeric_limits<storage_type>::max( ) );
        const unsigned long digit_modulus =
            static_cast<unsigned long>( numeric_limits<storage_type>::max( ) ) + 1;

        // Be sure the number is initialized to zero.
        digit_count = 0;
        digits = nullptr;

        while( value > 0UL ) {
            expand( );
            digits[digit_count - 1] = static_cast<storage_type>( value % digit_modulus );
            value = value / digit_modulus;
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

            // TODO: Find a better way to do this.
            // This works, but it relies on complex mathematical operations and implicit type
            // conversions from `unsigned long` to BigInteger. The fundamental complexity with
            // this method is that we are converting from a base 10 digit string to a base 2**32
            // digit stream.
            *this *= 10UL;
            *this += static_cast<unsigned long>( digit_character - '0' );
        }
     }


    BigInteger &BigInteger::operator+=( const BigInteger &right )
    {
        // First deal with the case when one (or both) of the numbers are zero. This is needed
        // because zero is represented in a special way.
        if( right.digit_count == 0 ) return *this;
        if( digit_count == 0 ) {
            digit_count = right.digit_count;
            if( digit_count != 0 ) {
                digits = new storage_type[digit_count];
                std::memcpy( digits, right.digits, digit_count * sizeof( storage_type ) );
            }
            return *this;
        }

        // Both numbers are non-zero...

        // How many digits do we have to process?
        const unsigned max_size =
            ( digit_count > right.digit_count ) ? digit_count : right.digit_count;

        storage_type other_digit;
        compute_type sum;
        compute_type carry = 0;

        // Process all digits...
        for( size_t digit_index = 0; digit_index < max_size; ++digit_index ) {

            // If I'm out of digits, I need to expand.
            if( digit_index > digit_count - 1 ) expand( );

            // If the other number is out of digits, use zero; otherwise use its digit.
            if( digit_index > right.digit_count - 1 ) {
                other_digit = 0;
            }
            else {
                other_digit = right.digits[digit_index];
            }

            const compute_type digit_modulus =
                static_cast<compute_type>( numeric_limits<storage_type>::max( ) ) + 1;

            // Do the addition. Note that if we try to add two digits directly, without first
            // casting one of them, the computation will be done in storage_type, which might
            // overflow.
            sum = static_cast<compute_type>( digits[digit_index] ) + other_digit + carry;
            digits[digit_index] = static_cast<storage_type>( sum % digit_modulus );
            carry = sum / digit_modulus;
        }

        // Handle an overall carry if there is one.
        if( carry != 0 ) {
            expand( );
            digits[digit_count - 1] = static_cast<storage_type>( carry );
        }
        return *this;
    }


    BigInteger &BigInteger::operator*=( const BigInteger &right )
    {
        // TODO: Finish Me!
        return *this;
    }


    BigInteger::operator unsigned long( )
    {
        unsigned long value = 0;

        // Handle the special case of zero.
        if( digit_count == 0 ) return value;

        size_t digit_index = digit_count - 1;

        const compute_type digit_modulus =
            static_cast<compute_type>( numeric_limits<storage_type>::max( ) ) + 1;

        while( digit_index >= 0 ) {
            value = ( digit_modulus * value ) + digits[digit_index];
            digit_index--;
        }
        // TODO: Add overflow check. We should probably throw an exception.
        return value;
    }


    // This method violates an invariant of the class. In particular, it creates a number with a
    // leading zero. This isn't a problem, however, because this method is private. It is the
    // responsibility of the calling method to reestablish the invariant before returning.
    // Clients of the BigInteger class are not aware of the temporarily invalid state of the
    // object.
    void BigInteger::expand( )
    {
        // Expanding zero entails adding a single digit.
        if( digits == nullptr ) {
            digits = new storage_type[1];
            digits[0] = 0;
        }
        else {
            // Otherwise allocate a new, slightly larger array and copy all the digits into it.
            // Set the new digit to zero for now. Note that this can get slow for very large
            // numbers of digits. It would be better to expand the array in blocks where the
            // block size increases each time the array is reallocated. That would require
            // keeping track of both the size of the array and the number of "actual" digits it
            // contains.
            storage_type *new_digits = new storage_type[digit_count + 1];
            std::memcpy( new_digits, digits, digit_count * sizeof( storage_type ) );
            new_digits[digit_count] = 0;
            delete []  digits;
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
        std::memmove( &digits[1], &digits[0], (digit_count - 1) * sizeof( storage_type ) );
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
            // digits. We need digit_index to be int so the test 'digit_index >= 0' can be
            // false.
            int digit_index = static_cast<int>( bi.digit_count ) - 1;

            // TODO: No, no, no, no. Not even close! Fix this!
            // Maybe print in hex as a temporary work-around? Otherwise we need to implement
            // division and modulus, which are hard.
            while( digit_index >= 0) {
                os << static_cast<char>( bi.digits[digit_index] + '0' );
                digit_index--;
            }
        }
        return os;
    }

}
