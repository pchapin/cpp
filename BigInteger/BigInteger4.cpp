
#include <iostream>
#include <cctype>
#include <cstring>
#include <limits>
#include "BigInteger4.hpp"

using namespace std;

namespace vtsu {

    BigInteger::BigInteger( unsigned long value )
    {
        static_assert( numeric_limits<unsigned long>::max( ) > numeric_limits<storage_type>::max( ) );
        const unsigned long digit_modulus =
            static_cast<unsigned long>( numeric_limits<storage_type>::max( ) ) + 1;

        while( value > 0UL ) {
            digits.push_back( static_cast<unsigned short>( value % digit_modulus ) );
            value = value / digit_modulus;
        }
    }


    BigInteger::BigInteger( const string &raw_digits )
    {
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
        if( right.digits.size( ) == 0 ) return *this;
        if( digits.size( ) == 0 ) {
            digits = right.digits;
            return *this;
        }

        // Both numbers are non-zero...

        // How many digits do we have to process?
        const unsigned max_size =
            ( digits.size( ) > right.digits.size( ) ) ? digits.size( ) : right.digits.size( );

        storage_type other_digit;
        compute_type sum;
        compute_type carry = 0;

        // Process all digits...
        for( vector<storage_type>::size_type digit_index = 0; digit_index < max_size; ++digit_index ) {
            
            // If I'm out of digits, I need to expand.
            if( digit_index > digits.size( ) - 1 ) digits.push_back( 0 );

            // If the other number is out of digits, use zero; otherwise use its digit.
            if( digit_index > right.digits.size( ) - 1 ) {
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
            digits.push_back( static_cast<storage_type>( carry ) );
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
        if( digits.size( ) == 0 ) return value;

        vector<storage_type>::size_type digit_index = digits.size( ) - 1;

        const compute_type digit_modulus =
            static_cast<compute_type>( numeric_limits<storage_type>::max( ) ) + 1;

        while( digit_index >= 0 ) {
            value = digit_modulus * value + digits[digit_index];
            digit_index--;
        }
        // TODO: Add overflow check. We should probably throw an exception.
        return value;
    }


    ostream &operator<<( ostream &os, const BigInteger &bi )
    {
        // The number zero must be handled as a special case.
        if( bi.digits.size( ) == 0 ) {
            os << '0';
        }
        else {
            // This is a little dangerous. What if the number of digits was greater than the
            // type int could represent? That happens for numbers with more than two billion
            // digits. We need digit_index to be int so the test 'digit_index >= 0' can be
            // false.
            int digit_index = static_cast<int>( bi.digits.size( ) ) - 1;

            // 
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
