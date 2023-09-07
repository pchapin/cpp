/*! \file    Time.cpp
 *  \brief   Implementation of clock times.
 *  \author  Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <ctime>
#include <iomanip>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>

#include "Time.hpp"

using namespace std;

namespace vtsu {

    // Private Methods
    // ===============

    void Time::set( unsigned hours, unsigned minutes, unsigned seconds )
    {
        // Compute the total number of seconds in the incoming time.
        long total = hours * 3600L + minutes * 60L + seconds;

        this->seconds = total % 60L;
        total = total / 60L;

        this->minutes = total % 60L;
        total = total / 60L;

        this->hours   = total % 24L;
    }


    // Public Methods
    // ==============

    Time::Time( )
    {
        hours   = 0;
        minutes = 0;
        seconds = 0;
    }


    Time::Time( unsigned hours, unsigned minutes, unsigned seconds )
    {
        set( hours, minutes, seconds );
    }


    Time::Time( const string &time_string )
    {
        // The regular expression below matches a string of the form HH:MM:DD except that the
        // components of the time are arbitrary unsigned integers.
        regex  date_matcher{ R"((\d+):(\d+):(\d+))" };
        smatch matches;

        // Try to match the entire string. If the match files, set the Time object to 00:00:00.
        if( !regex_match( time_string, matches, date_matcher ) ) {
            hours = minutes = seconds = 0;
            return;
        }

        // The first alternative matched. Extract the sub-matches.
        int incoming_hours   = stoi( matches[1] );  // Note: no range checking here!
        int incoming_minutes = stoi( matches[2] );
        int incoming_seconds = stoi( matches[3] );

        // Delegate to Time::set( unsigned, unsigned, unsigned ) the task of wrapping values and
        // installing the time into the object. Notice the type mismatch going from integers to
        // unsigned integers. This is relatively okay since the matched integers are guaranteed
        // to be positive. However, we sacrifice the ability to use a time string with extremely
        // large time components (e.g., "4000000000:0:0").
        set( incoming_hours, incoming_minutes, incoming_seconds );
        return;
    }


    unsigned Time::get_hours( ) const
    {
        return hours;
    }


    unsigned Time::get_minutes( ) const
    {
        return minutes;
    }


    unsigned Time::get_seconds( ) const
    {
        return seconds;
    }

    Time Time::roll_forward_seconds( unsigned delta ) const
    {
        // TODO: Finish me!
        return Time( );
    }


    Time Time::roll_forward_minutes( unsigned delta ) const
    {
        // TODO: Finish me!
        return Time( );
    }


    Time Time::roll_forward_hours( unsigned delta ) const
    {
        // TODO: Finish me!
        return Time( );
    }


    // Free Functions
    // ==============

    int operator-( const Time &future, const Time &past )
    {
        int result = 0;
        // TODO: Finish me!
        return result;
    }


    ostream &operator<<( ostream &output, const Time &the_time )
    {
        char original_fill = output.fill( );
        int  original_width = output.width( );
        auto flags = output.flags( );

        // C++ does not allow nested functions, but it does allow *lambda expressions* which are
        // essentially unnamed functions. Here I define a lambda expression that prints a given
        // fill character enough times to fill the given width. The value of 'i' starts at 10
        // because the Date3 object itself is 10 characters wide and must also occupy the same
        // field.
        auto print_fill = []( ostream &output, char fill, int width ) -> void {
            for( int i = 10; i < width; ++i ) {
                output << fill;
            }
        };

        // Replace the caller's requested width with the default width. This is needed so that
        // when we output fill characters first (e.g., when the caller requests right
        // justification), the first fill character won't itself be filled to the caller's
        // width.
        output.width( 0 );

        // If we are trying to right justify, print the caller's fill character as needed before
        // printing the Date3 object.
        if( flags & ios_base::right ) {
            print_fill( output, original_fill, original_width );
        }

        // Print the actual Date3 object.
        output << setfill( '0' );
        output << setw( 2 ) << the_time.get_hours( )   << ':';
        output << setw( 2 ) << the_time.get_minutes( ) << ':';
        output << setw( 2 ) << the_time.get_seconds( );
        output << setfill( original_fill );

        // If we are not trying to right justify (meaning we are being explicitly asked to left
        // justify OR no specific justification is requested), print the caller's fill character
        // as needed after printing the Date3 object.
        if( !( flags & ios_base::right ) ) {
            print_fill( output, original_fill, original_width );
        }
        return output;
    }

}
