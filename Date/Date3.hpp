/*! \file    Date3.hpp
 *  \brief   Interface to calendar dates.
 *  \author  Peter Chapin <peter.chapin@vermontstate.edu>
 * 
 * This class is used in CIS-3012, the C++ Programming class at Vermont State University. It
 * serves as an example of a simple class. An earlier version of the class is in Date2.hpp.
 * 
 * The changes from Date2 are:
 * 
 * + The constructor taking a string is now 'explicit' to suppress unwanted conversions.
 * + The inline accessor methods are now defined inside the class body.
 * + The relational operators are now generated from the spaceship operator.
 * + A lambda expression is used in the implementation of operator<<( ) as a demonstration.
 */

#ifndef DATE_HPP
#define DATE_HPP

#include <compare>     // Needed for spaceship operator.
#include <iosfwd>
#include <stdexcept>
#include <string>

namespace vtsu {

    //! Class representing calendar dates.
    /*!
     * Date objects handle dates between Jan 1, 1950 and Dec 31, 2199. Any attempt to set a Date
     * outside that range, either directly or by way of a computation, will cause an exception
     * to be thrown. This limited range is intended to be broad enough to be useful without
     * bumping up against issues of calendar reform that occurred during the 16th through 20th
     * centuries. See: https://www.timeanddate.com/calendar/julian-gregorian-switch.html.
     *
     * The interface to Dates uses 1-based numbering: January is month 1, February is month 2,
     * and so on. Furthermore, the first day of the month is day 1. Years must be full, four
     * digit years.
     * 
     * On output, Dates are converted to strings using the standard format of yyyy-mm-dd where
     * the month and the day are always exactly two digits. On input, an additional string
     * format may be used: mm/dd/yyyy where the month and the day may be one or two digits.
     */
    class Date {
    public:

        /*!
         * Instances of this class are thrown when an attempt is made to create a Date that is
         * outside the allowed range. In this context the "allowed range" is any date with a
         * year between Date::minimum_year and Date::maximum_year inclusive.
         */
        class OutOfRange : public std::runtime_error {
            public:
                OutOfRange( const std::string &message ) : std::runtime_error( message ) { }
        };

        /*!
         * Instances of this class are thrown when an attempt is made to construct or set a
         * Date to an invalid date that is otherwise inside the allowed range.
         */
        class Invalid : public std::runtime_error {
            public:
                Invalid( const std::string &message ) : std::runtime_error( message ) { }
        };

        static const int minimum_year = 1950;
        static const int maximum_year = 2199;

        //! Default constructor.
        /*!
         * This constructor initializes the Date to the minimum date of January 1,
         * Date::minimum_year.
         */
        Date( );

        //! Initialize to an arbitrary date.
        /*!
         * The year must be a full, four-digit integer.
         *
         * \param year The year in the range Date::minimum_year .. Date::maximum_year
         * \param month The month in the range 1 .. 12
         * \param day The day in the range 1 .. 31
         * 
         * \throws OutOfRange if the year is outside the allowed range.
         * \throws Invalid if the month or day are outside of their allowed ranges, after
         * considering the leap year rules. In cases where a Date is constructed with invalid
         * values *and* an out of range year, the OutOfRange exception is thrown.
         */
        Date( int year, int month, int day );

        //! Initialize using a string representation of a date.
        /*! 
         * \throws OutOfRange if the year is outside the allowed range.
         * \throws Invalid if the month or day are outside of their allowed ranges, after
         * considering the leap year rules, or if the string representation can't be parsed. In
         * cases where a Date is constructed with invalid values *and* an out of range year,
         * the OutOfRange exception is thrown.
         */
        explicit Date( const std::string &date_string );

        //! Set an existing Date to a new date.
        /*!
         * The year must be a full, four-digit integer. If an exception is thrown the value of
         * the Date is left unchanged.
         *
         * \param year The year in the range Date::minimum_year .. Date::maximum_year
         * \param month The month in the range 1 .. 12
         * \param day The day in the range 1 .. 31
         * 
         * \throws OutOfRange if the year is outside the allowed range.
         * \throws Invalid if the month or day are outside of their allowed ranges, after
         * considering the leap year rules. In cases where a Date is constructed with invalid
         * values *and* an out of range year, the OutOfRange exception is thrown.
         */
        void set( int year, int month, int day );

        //! Set an existing Date to a new date using a string representation of a date.
        /*!
         * If an exception is thrown the value of the Date is left unchanged.
         * 
         * \throws OutOfRange if the year is outside the required range.
         * \throws Invalid if the month or day are outside of their required ranges, after
         * considering the leap year rules, or if the string representation can't be parsed. In
         * cases where a Date is constructed with invalid values *and* an out of range year, the
         * OutOfRange exception is thrown.
         */
        void set( const std::string &date_string );

        //! Returns the year of this Date (range Date::minimum_year .. Date::maximum_year).
        int get_year( ) const
            { return year; }

        //! Returns the month of this Date (in the range 1 .. 12).
        int get_month( ) const
            { return month; }

        //! Returns the day of this Date (in the range range 1 .. 31).
        int get_day( ) const
            { return day; }

        //! Advance the date by a given number of days.
        /*!
         * This method modifies the Date in-place. If delta is negative this function will move
         * the date backwards.
         *
         * \param delta The number of days to advance the date. Negative values are allowed.
         * 
         * \throws OutOfRange if this method would generate a date outside the allowed range. In
         * that case, the original Date object is left unchanged.
         */
        void advance( long delta = 1 );

        // The "spaceship" operator is used to generate all the relational operators. The use of
        // 'default' asks the compiler to automatically generate the spaceship operator itself
        // (which isn't required; you could implement the spaceship operator manually if
        // necessary). This is works here because all the data members of Date are comparable
        // via '<=>' and they are declared in an appropriate order in the class definition.
        //
        // In general, the spaceship operator returns a std::strong_ordering object. This object
        // can be compared to zero to determine the relationship between the two operands. The
        // use of 'auto' here asks the compiler to deduce the return type of the operator.
        auto operator<=>( const Date &other ) const = default;

    private:

        // This representation makes Date I/O easy, but Date computations awkward. The order in
        // which these members appear is required by the spaceship operator's default
        // implementation.
        int year, month, day;

        // Private Methods
        bool is_leap( ) const;       // Return true if the current year is a leap year.
        int  month_length( ) const;  // Return the number of days in the current month.
        void next( );                // Advances the date by one day.
        void previous( );            // Backs up the date by one day.
    };


    // Free Functions
    // ==============

    //! Computes how many days difference there is between two dates.
    /*!
     * The return value is zero if 'future' and 'past' are the same date, positive if 'future'
     * comes after 'past', and negative otherwise.
     * 
     * \todo Is the return type of 'long' the best choice here? Perhaps 'int' would be good
     * enough. How many days are in the range Jan 1, Date::minimum_year to Dec 31,
     * Date::maximum_year?
     */
    long difference( const Date &future, const Date &past );

    //! Writes a Date to an output stream.
    std::ostream &operator<<( std::ostream &output, const Date &the_date );

    //! Reads a Date from an input stream.
    std::istream &operator>>( std::istream &input, Date &the_date );
}

#endif
