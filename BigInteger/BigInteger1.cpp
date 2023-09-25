/*! \file   BigInteger1.cpp
 *  \brief  A "first generation" definition of an extended precision integer class.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <algorithm>
#include <cctype>           // Contains std::isdigit and other facilities from C's ctype.h.
#include <cstring>          // Contains std::memset and other facilities from C's string.h.
#include "BigInteger1.hpp"

using namespace std;

namespace vtsu {

    // Default initializes the BigInteger to zero.
    BigInteger::BigInteger( )
    {
        memset( digits, 0, sizeof( digits ) );
    }


    BigInteger::BigInteger( unsigned long value )
    {
        // Zero out all the digits.
        memset( digits, 0, sizeof( digits ) );

        // This static_assert is a compile time check. It will cause a compile time error if the
        // condition is false. Because it is processed by the compiler, it can only make use of
        // constants known to the compiler. Here we are checking that the size of the digits
        // array is sufficient to hold the digits of the largest possible unsigned long (64 bits).
        //
        // TODO: This check is not sufficient in the case where unsigned long is, e.g., 128 bits.
        static_assert( maximum_size >= 20, "maximum_size is too small" );

        size_t digit_index = 0;
        while( value > 0 ) {
            // The `static_cast` operator does "safe" type conversions.
            digits[digit_index] = static_cast<int>( value % 10 );
            value /= 10;
            ++digit_index;
        }
    }


    BigInteger::BigInteger( const string &raw_digits )
    {
        // Zero out all the digits.
        memset( digits, 0, sizeof( digits ) );

        // Check to ensure all characters of the string are digits.
        for_each( raw_digits.begin( ), raw_digits.end( ), []( char c ) {
            if( !isdigit( c ) )
                throw InvalidFormat( "Non-digit in BigInteger::BigInteger( const string & )" );
        } );

        // Find the first non-zero digit.
        string::size_type first_non_zero_digit_position = raw_digits.find_first_not_of( '0' );

        // If the string is all zero digits, we're done.
        if( first_non_zero_digit_position == string::npos ) return;

        // If the string has too many digits, throw an exception.
        if( raw_digits.length( ) - first_non_zero_digit_position > maximum_size ) {
            throw std::overflow_error( "Overflow in BigInteger::BigInteger( const string & )" );
        }

        size_t digit_index = 0;
        string::size_type current_digit_position = raw_digits.length( ) - 1;

        // Unsigned types are tricky to handle because decrementing an unsigned value will never
        // drop below zero. Thus tests like current_digit_position >= 0 will always be true. For
        // this reason it is usually better (even necessary) to run loops that count upward the
        // appropriate number of times rather than downward.
        for( size_t i = 0; i < raw_digits.length( ) - first_non_zero_digit_position; ++i ) {
            // NOTE: There are assumptions being made about how digit characters are represented.
            digits[digit_index] = raw_digits[current_digit_position] - '0';
            --current_digit_position;
            ++digit_index;
        }
    }


    int BigInteger::number_of_digits( ) const
    {
        // Count leading zeros.
        size_t leading_zeros = 0;
        size_t digit_index = maximum_size - 1;

        // Again, we use an upward counting loop because of the unsigned type.
        for( size_t i = 0; i < maximum_size; ++i ) {
            if( digits[digit_index] != 0 ) break;
            ++leading_zeros;
            --digit_index;
        }
        return maximum_size - leading_zeros;
    }


    BigInteger &BigInteger::operator+=( const BigInteger &right )
    {
        int sum;
        int carry = 0;

        for( size_t digit_index = 0; digit_index < maximum_size; ++digit_index ) {
            sum = digits[digit_index] + right.digits[digit_index] + carry;
            digits[digit_index] = sum % 10;
            carry = sum / 10;
        }
        // TODO: *this is changed even if an exception is thrown. Is that OK? (probably not)
        if( carry != 0 ) throw std::overflow_error( "Overflow in BigInteger::operator+=" );
        return *this;
    }


    BigInteger &BigInteger::operator-=( const BigInteger &right )
    {
        // TODO: Implement me!
        throw NotImplemented( "BigInteger::operator-=" );
        return *this;
    }


    BigInteger &BigInteger::operator*=( const BigInteger &right )
    {
        // TODO: Implement me!
        throw NotImplemented( "BigInteger::operator*=" );
        return *this;
    }


    BigInteger &BigInteger::operator/=( const BigInteger &right )
    {
        // TODO: Implement me!
        throw NotImplemented( "BigInteger::operator/=" );
        return *this;
    }


    BigInteger &BigInteger::operator%=( const BigInteger &right )
    {
        // TODO: Implement me!
        throw NotImplemented( "BigInteger::operator%=" );
        return *this;
    }


    BigInteger::operator unsigned long( ) const
    {
        unsigned long long value = 0;
        int digit_index = maximum_size - 1;

        while( digit_index >= 0 ) {
            value = 10 * value + digits[digit_index];
            digit_index--;
        }
        // TODO: Add overflow check.
        return value;
    }


    ostream &operator<<( ostream &os, const BigInteger &bi )
    {
        size_t digit_count = bi.number_of_digits( );

        // The number zero must be handled as a special case.
        if( digit_count == 0 ) {
            os << '0';
        }
        else {
            size_t digit_index = digit_count - 1;

            // Another upward counting loop because of the unsigned type.
            for( size_t i = 0; i < digit_count; i++ ) {
                os << static_cast<char>( bi.digits[digit_index] + '0' );
                --digit_index;
            }
        }
        return os;
    }


}
