/*! \file    Date1.cpp
 *  \brief   Implementation of calendar dates.
 *  \author  Peter Chapin <peter.chapin@vermontstate.edu>
 * 
 *  \note The comments here should discuss *only* internal, implementation-specific issues. Any
 * thing of interest to the class's clients should be documented in the header file.
 */

// BP: I recommend including headers in alphabetical order. If the headers are written properly,
// the order shouldn't matter. However, finding a header in a long list is easier if they are
// sorted.
#include <ctime>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>

// BP: I recommend including third-party library headers in alphabetical order *between* the
// standard library headers and the project-specific headers. NOTE: This program does not make
// use of any third-party library headers.

// BP: I recommend including project-specific headers in alphabetical order *after* all the
// standard library headers and third-party library headers have been included.
//
// BP: I recommend that you include standard library headers and third-part library headers that
// you need for the code in this file even if you *know* they are already included in your
// project-specific headers. Including a header multiple times should cause no problems, and
// this practice allows you to edit includes inside project-specific headers without concerns
// about the impact doing so might have on the rest of your program.
#include "Date1.hpp"

// BP: I recommend that you use a using directive for the std namespace in the .cpp file. This
// is acceptable because all C++ programmers should be familiar with the contents of the std
// namespace. This is *not* acceptable in header files because it can pollute the namespace of
// the client code.
using namespace std;

namespace vtsu {

    // Private Methods
    // ===============

    bool Date::is_leap( ) const
    {
        bool result = false;

        if(           ( year %   4 == 0 ) ) result = true;
        if( result && ( year % 100 == 0 ) ) result = false;
        if(!result && ( year % 400 == 0 ) ) result = true;

        return result;
    }


    int Date::month_length( ) const
    {
        // Lookup table gives number of days in each month.
        static const int month_lengths[] = {
            31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
        };

        int length = month_lengths[month - 1];

        // Now perhaps make a correction if the month is February.
        if( month == 2 && is_leap( ) ) length++;

        return length;
    }


    // This method has to deal with the fact that the number of days in each month is different.
    // Furthermore, the number of days in February is a function of the year. Notice that this
    // method does not attempt to restore the state of a Date object if an exception is thrown.
    // That is the responsibility of the caller.
    void Date::next( )
    {
        // Try incrementing the day. If it overflows the month, make a correction, etc.
        if( ++day > month_length( ) ) {
            day = 1;
            if( ++month > 12 ) {
                month = 1;
                ++year;
                if( year > maximum_year )
                    throw OutOfRange( "Date overflow in Date::next( )" );
            }
        }
    }


    // This method works similarly to Date::next().
    void Date::previous( )
    {
        bool fix_day = false;

        // Try decrementing the day.
        if( --day < 1 ) {
            fix_day = true;
            if( --month < 1 ) {
                month = 12;
                --year;
                if( year < minimum_year )
                    throw OutOfRange( "Date underflow in Date::previous( )" );
            }
        }

        // If we wrapped over a month boundary, set the day to the last day of the new month.
        if( fix_day ) day = month_length( );
    }


    // Public Methods
    // ==============

    Date::Date( )
    {
        year  = minimum_year;
        month = 1;
        day   = 1;
    }


    Date::Date( int year, int month, int day)
    {
        set( year, month, day );
    }


    void Date::set( int year, int month, int day )
    {
        // First check if the date is out of range or definitely invalid.
        if( year < minimum_year || year > maximum_year )
            throw OutOfRange( "Date out of range in Date::set( int, int, int )" );

        if( month < 1 || month > 12 )
            throw Invalid( "Invalid month in Date::set( int, int, int )" );

        if( day < 1 || day > 31 )
            throw Invalid( "Invalid day in Date::set( int, int, int )" );

        // Back up this Date's current state.
        Date backup = *this;

        // Install the new date information.
        this->year = year; this->month = month; this->day = day;

        // Check if the new day is valid in the context of the date. If not, restore the
        // original state.
        if ( this->day > month_length( ) ) {
            *this = backup;
            throw Invalid( "Invalid day in Date::set( int, int, int )" );
        }
    }


    void Date::set( const string &date_string )
    {
        // The regular expression below matches a string of the form YYYY-MM-DD.
        regex  date_matcher{ R"((\d{4})-(\d{2})-(\d{2}))" };
        smatch matches;

        // Try to match the entire string.
        if( !regex_match( date_string, matches, date_matcher ) ) {
            throw Invalid( "Invalid date string format in Date::set( const std::string & )" );
        }

        // Extract the sub-matches.
        int incoming_year  = stoi( matches[1] );
        int incoming_month = stoi( matches[2] );
        int incoming_day   = stoi( matches[3] );

        // Delegate to Date::set( int, int, int ) the task of checking the values and throwing
        // exceptions if necessary.
        set( incoming_year, incoming_month, incoming_day );
    }


    int Date::get_year( ) const
    {
        return year;
    }


    int Date::get_month( ) const
    {
        return month;
    }


    int Date::get_day( ) const
    {
        return day;
    }


    void Date::advance( long delta )
    {
        long count;

        // If delta == 0 we're done already.
        if( delta == 0 ) return;

        // Back up this Date's current state.
        Date backup = *this;

        try {
            // If we're trying to step forward...
            if( delta >  0 ) {
                for( count = delta; count > 0; count-- ) next( );
            }

            // We're trying to step backward...
            else {
                for( count = -delta; count > 0; count-- ) previous( );
            }
        }

        // If we go off the end of the allowed range, restore the original state and rethrow.
        catch( Date::OutOfRange & ) {
            *this = backup;
            throw;
        }
    }


    // Free Functions
    // ==============

    bool operator==( const Date &left, const Date &right )
    {
        if( left.get_year( )  == right.get_year( )  &&
            left.get_month( ) == right.get_month( ) &&
            left.get_day( )   == right.get_day( )     ) return true;

        return false;
    }


    bool operator!=( const Date &left, const Date &right )
    {
        return !( left == right );
    }


    bool operator<( const Date &left, const Date &right )
    {
        if( left.get_year( ) <  right.get_year( ) ) return true;
        if( left.get_year( ) == right.get_year( ) ) {
            if( left.get_month( ) <  right.get_month( ) ) return true;
            if( left.get_month( ) == right.get_month( ) ) {
                if( left.get_day( ) <  right.get_day( ) ) return true;
            }
        }
        return false;
    }


    bool operator<=( const Date &left, const Date &right )
    {
        return ( left < right ) || ( left == right );
    }


    bool operator>( const Date &left, const Date &right )
    {
        return !( left <= right );
    }


    bool operator>=( const Date &left, const Date &right )
    {
        return !( left < right );
    }


   long difference( const Date &future, const Date &past )
    {
        long result = 0;

        // Handle the simple case first.
        if( future == past ) return 0;

        // Make copies of the parameters that I can change.
        Date my_future{ future };
        Date my_past{ past };

        // If my_past is small, advance it until it matches my_future.
        // This will never throw an exception because both dates are valid.
        while( my_future > my_past ) {
            my_past.advance( 1 );
            result++;
        }

        // If my_future is small, advance it until it matches my_past.
        // This will never throw an exception because both dates are valid.
        while( my_past > my_future ) {
            my_future.advance( 1 );
            result--;
        }

        return result;
    }


    ostream &operator<<( ostream &output, const Date &the_date )
    {
        char original_fill = output.fill( );
        int  original_width = output.width( );

        output << setfill( '0' );
        output << setw( 4 ) << the_date.get_year( )  << '-';
        output << setw( 2 ) << the_date.get_month( ) << '-';
        output << setw( 2 ) << the_date.get_day( );
        output << setfill( original_fill );

        for( int i = 10; i < original_width; ++i ) {
            output << original_fill;
        }
        return output;
    }


    istream &operator>>( istream &input, Date &the_date )
    {
        string date_string;

        // Get a single word from the input stream. Delegate the problem of parsing it and
        // checking it to the Date::set( const string & ) method. If Date::set( const string &
        // ) throws an exception, 'the_date' will not be changed.

        input >> date_string;
        the_date.set( date_string );

        return input;
    }

}
