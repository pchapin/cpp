/*! \file    Date2.cpp
 *  \brief   Implementation of calendar dates.
 *  \author  Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <ctime>
#include <iomanip>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "Date2.hpp"

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
        // The regular expression below matches a string of the form YYYY-MM-DD or of the form
        // MM/DD/YYYY. In the second case, the month and day can be one or two digits. The year
        // must always be four digits.
        regex  date_matcher{ R"(((\d{4})-(\d{2})-(\d{2}))|((\d{1,2})/(\d{1,2})/(\d{4})))" };
        smatch matches;

        // Try to match the entire string.
        if( !regex_match( date_string, matches, date_matcher ) ) {
            throw Invalid( "Invalid date string format in Date::set( const std::string & )" );
        }

        // Which alternative matched?
        if( matches[1].matched ) {
            // The first alternative matched. Extract the sub-matches.
            int incoming_year  = stoi( matches[2] );
            int incoming_month = stoi( matches[3] );
            int incoming_day   = stoi( matches[4] );

            // Delegate to Date::set( int, int, int ) the task of checking the values and
            // throwing exceptions if necessary.
            set( incoming_year, incoming_month, incoming_day );
            return;
        }
        else if( matches[5].matched ) {
            // The second alternative matched. Extract the sub-matches.
            int incoming_month = stoi( matches[6] );
            int incoming_day   = stoi( matches[7] );
            int incoming_year  = stoi( matches[8] );

            // Delegate to Date::set( int, int, int ) the task of checking the values and
            // throwing exceptions if necessary.
            set( incoming_year, incoming_month, incoming_day );
            return;
        }
        else {
            // This should never happen.
            throw logic_error( "Internal error in Date::set( const std::string & )" );
        }
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
        auto flags = output.flags( );

        // Replace the caller's requested width with the default width. This is needed so that
        // when we output fill characters first (e.g., when the caller requests right
        // justification), the first fill character won't itself be filled to the caller's
        // width.
        output.width( 0 );

        // If we are trying to right justify, print the caller's fill character as needed before
        // printing the Date object.
        if( flags & ios_base::right ) {
            for( int i = 10; i < original_width; ++i ) {
                output << original_fill;
            }
        }

        // Print the actual Date object.
        output << setfill( '0' );
        output << setw( 4 ) << the_date.get_year( )  << '-';
        output << setw( 2 ) << the_date.get_month( ) << '-';
        output << setw( 2 ) << the_date.get_day( );
        output << setfill( original_fill );

        // If we are not trying to right justify (meaning we are being explicitly asked to left
        // justify OR no specific justification is requested), print the caller's fill character
        // as needed after printing the Date object.
        if( !( flags & ios_base::right ) ) {
            for( int i = 10; i < original_width; ++i ) {
                output << original_fill;
            }
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
