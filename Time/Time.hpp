/*! \file    Time.hpp
 *  \brief   Interface to clock times.
 *  \author  Peter Chapin <peter.chapin@vermontstate.edu>
 * 
 * This class is a homework assignment for CIS-3012, the C++ Programming class at Vermont State
 * University.
 */

#ifndef TIME_HPP
#define TIME_HPP

#include <compare>     // Needed for spaceship operator.
#include <iosfwd>
#include <stdexcept>
#include <string>

namespace vtsu {

    //! Class representing clock times.
    /*!
     * This class represents clock times. The interface to this class uses 24 hour time in the
     * range 00:00:00 to 23:59:59. All computations on times wrap so that, for example,
     * advancing 23:59:59 by one second produces 00:00:00. Out of range times do not exist. If
     * an attempt is made to create a Time object with an out of range value, the time simply
     * wraps as much as necessary to bring the value in range.
     * 
     * It is also not possible to set a Time object to an invalid value. For example, if you
     * attempt to set a Time object to 25:00:00, the time will wrap around to 01:00:00. If you
     * attempt to set a Time object to 00:60:00, the time will wrap around to 01:00:00, etc.
     * 
     * This class does not support fractional seconds. The smallest unit of time is one second.
     * 
     * This class is immutable; once a Time object has been constructed, it cannot be changed.
     * Methods that appear to change the Time object actually return a new Time object with the
     * desired value. One consequence of this is that there is no operator>>( ) for Time
     * objects. Clients must accept times from the user as strings and then use the appropriate
     * constructor to convert those strings into Time objects.
     */
    class Time {
    public:

        //! Default constructor.
        /*!
         * This constructor initializes the Time object to 00:00:00.
         */
        Time( );

        //! Initialize to an arbitrary time.
        /*!
         * \param hours The number of hours desired
         * \param minutes The number of minutes desired
         * \param seconds The number of seconds desired
         * 
         * Out of range or invalid values wrap around as many times as necessary to bring the
         * the value in range. The default arguments allow this constructor to be called with
         * one, two, or three arguments, as desired. The use of unsigned integers rules out any
         * possibility of negative values, which are problematic in the context of wrap-around
         * semantics.
         */
        Time( unsigned hours, unsigned minutes = 0U, unsigned seconds = 0U );

        //! Initialize using a string representation of a time.
        /*! 
         * The time string must be in the form "hh:mm:ss" where hh is the hours, mm is the
         * minutes, and ss is the seconds. However, each component can be an arbitrary
         * (unsigned) integer. For example, "0:1:500" is a time string that represents 00:09:20.
         * If an invalid time string is given (i.e., one that has the wrong format), the time is
         * set to 00:00:00.
         * 
         * Implementation Hint: Create a private helper method that deals with the wrap-around
         * and sets the data members directly. Then call that method from both constructors.
         */
        explicit Time( const std::string &time_string );

        /*
         * This declaration prevents the compiler from generating the copy assignment operator.
         * Since Time objects are intended to be immutable, it doesn't make sense to allow them
         * to be assigned to each other. Note that the generated copy constructor is fine. You
         * can still initialize a Time object from another Time object.
         *
         * Implementation Hint: You do not need to implement this method or do anything about
         * this method. This declaration is here to prevent the compiler from generating it
         * automatically.
         */
        Time &operator=( const Time & ) = delete;

        //! Returns the hours of this Time (always in the range 0 .. 23).
        unsigned get_hours( ) const;

        //! Returns the minutes of this Time (always in the range 0 .. 59).
        unsigned get_minutes( ) const;

        //! Returns the seconds of this Time (always in the range 0 .. 59).
        unsigned get_seconds( ) const;

        //! Advance the time by a given number of seconds.
        /*!
         * This method computes a new time by advancing 'this' time by the specified number of
         * seconds. This method does not modify 'this' time, but instead returns a new time with
         * the desired value.
         *
         * \param delta The number of seconds to advance the time.
         */
        Time roll_forward_seconds( unsigned delta = 1U ) const;

        //! Advance the time by a given number of minutes.
        /*!
         * This method computes a new time by advancing 'this' time by the specified number of
         * minutes. This method does not modify 'this' time, but instead returns a new time with
         * the desired value.
         * 
         * \param delta The number of minutes to advance the time.
         */
        Time roll_forward_minutes( unsigned delta = 1U ) const;

        //! Advance the time by a given number of hours.
        /*!
         * This method computes a new time by advancing 'this' time by the specified number of
         * hours. This method does not modify 'this' time, but instead returns a new time with
         * the desired value.
         * 
         * Implementation Hint: Both roll_forward_minutes( ) and roll_forward_hours( ) can be
         * implemented as inline methods that call roll_forward_seconds( ).
         * 
         * \param delta The number of hours to advance the time.
         */
        Time roll_forward_hours( unsigned delta = 1U ) const;

        // We will leave these unimplemented for now, but they are obvious extensions.
        //Time roll_backward_seconds( unsigned delta = 1U ) const;
        //Time roll_backward_minutes( unsigned delta = 1U ) const;
        //Time roll_backward_hours( unsigned delta = 1U ) const;

        // The "spaceship" operator is used to generate all the relational operators.
        //
        // Implementation hint: You do not need to implement this method. The compiler will
        // generate it automatically.
        auto operator<=>( const Time &other ) const = default;

    private:
        unsigned hours, minutes, seconds;

        // A private method to handle the wrap-around semantics is used by both constructors.
        void set( unsigned hours, unsigned minutes, unsigned seconds );
    };


    // Free Functions
    // ==============

    //! Computes how many seconds difference there is between two times.
    /*!
     * The return value is zero if 'future' and 'past' are the same time, positive if 'future'
     * comes after 'past', and negative otherwise. Notice that the return type is signed
     * because the difference can be negative if the first time comes before the second. For
     * example: Time( "00:01:00" ) - Time( "00:01:01" ) == -1.
     * 
     * Portability Note: The maximum difference between two times is 86,399 seconds. This might
     * be outside the range of int on some systems. However, systems that use 32-bit integers
     * will be able to represent this value without difficulty. For maximum portability, the
     * type long could be used instead of int. However, this would be overkill on systems that
     * use 64-bit long integers, and would waste memory on such systems.
     */
    int operator-( const Time &future, const Time &past );

    //! Writes a Time to an output stream.
    std::ostream &operator<<( std::ostream &output, const Time &the_time );
}

#endif
