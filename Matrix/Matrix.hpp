/*! \file   Matrix.hpp
 *  \brief  A class for representing matrices of floating point values.
 *  \author [YOUR NAME]
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <initializer_list>
#include <iosfwd>
#include <stdexcept>
#include <string>

// Whatever you do, do NOT use "using namespace std;" in a header file!

namespace vtsu {

    template<typename T>
    class Matrix {
    public:
        //! An unsigned type used for indexing the rows and columns of a Matrix.
        using index_type = std::size_t;

        /*!
         * Instances of this class are thrown when an attempt to create a Matrix with either
         * zero rows or zero columns is made, or when a math operation is attempted that does
         * not make sense due to incompatible dimensions.
         */
        class InvalidSize : public std::logic_error {
        public:
            explicit InvalidSize( const std::string &message ) :
                std::logic_error( message )
            { }
        };

        /*!
         * Instances of this class are thrown when an attempt to access a Matrix out of bounds
         * is made.
         */
        class OutOfBoundsIndex : public std::logic_error {
        public:
            explicit OutOfBoundsIndex( const std::string &message ) :
                std::logic_error( message )
            { }
        };

        //! Constructs a matrix with all elements initialized to zero.
        /*!
         * Once a Matrix has been created, its size cannot be changed (although the values of
         * the elements can be).
         *
         * \param row_count The number of rows in the Matrix.
         * \param column_count The number of columns in the Matrix.
         *
         * \throws InvalidSize if either row_count or column_count is zero.
         */
        Matrix( index_type row_count, index_type column_count );

        //! Initializer list constructor.
        /*!
         * This constructor allows a Matrix to be initialized using an initializer list of
         * initializer lists. The outer initializer list represents the rows of the Matrix, and
         * the inner initializer lists represent the columns of a particular row.
         *
         * \throws InvalidSize if the rows are not of equal length, or if the number of rows or
         * the number of columns is zero.
         */
        Matrix( std::initializer_list<std::initializer_list<T>> init_list );

        //! Destructor.
        ~Matrix( );

        //! Copy constructor.
        Matrix( const Matrix &other );

        //! Copy assignment operator.
        Matrix &operator=( const Matrix &other );

        //! Move constructor.
        Matrix( Matrix &&other );

        //! Move assignment operator.
        Matrix &operator=( Matrix &&other );

        // Return the dimensions of this Matrix.
        index_type rows( ) const
        { return row_count; }

        index_type columns( ) const
        { return column_count; }

        //! Read only access to a matrix element.
        /*!
         * e.g.:
         *
         * Matrix<double> m{ 2, 5 };
         * double d = m(1, 4);  // Read from value in lower right corner.
         *
         * \throws OutOfBoundsIndex if either index is out of bounds.
         */
        T operator()( index_type row, index_type column ) const;

        //! Read/Write access to a matrix element.
        /*!
         * e.g.:
         *
         * Matrix<double> m{ 2, 5 };
         * m(1, 4) = 3.14159;  // Write to value in lower right corner.
         *
         * \throws OutOfBoundsIndex if either index is out of bounds.
         */
        T &operator()( index_type row, index_type column );

        // Matrix math. Throws InvalidSize if incompatible matrix dimensions are used.
        Matrix &operator+=( const Matrix &other );
        Matrix &operator-=( const Matrix &other );
        Matrix &operator*=( const Matrix &other );

    private:
        index_type row_count;
        index_type column_count;

        // The intent is for the data to be stored in row major order.
        T *elements;
    };

    // Free Functions
    // ==============

    template<typename T>
    inline Matrix<T> operator+( const Matrix<T> &left, const Matrix<T> &right )
    {
        Matrix<T> temp{ left };
        temp += right;
        return temp;
    }

    template<typename T>
    inline Matrix<T> operator-( const Matrix<T> &left, const Matrix<T> &right )
    {
        Matrix<T> temp{ left };
        temp -= right;
        return temp;
    }

    template<typename T>
    inline Matrix<T> operator*( const Matrix<T> &left, const Matrix<T> &right )
    {
        Matrix<T> temp{ left };
        temp *= right;
        return temp;
    }

    //! Output a Matrix to the given ostream.
    template<typename T>
    std::ostream &operator<<( std::ostream &output, const Matrix<T> &m )
    {
        output << "[\n";
        for( typename Matrix<T>::index_type i = 0; i < m.row_count( ); ++i ) {
            output << "  [ ";
            for( typename Matrix<T>::index_type j = 0; j < m.column_count( ); ++j ) {
                const char *column_terminator = ( j < m.column_count( ) - 1 ) ? ", " : " ";
                output << m( i, j ) << column_terminator;
            }

            const char *row_terminator = ( i < m.row_count( ) - 1 ) ? "],\n" : "]\n";
            output << row_terminator;
        }
        output << "]\n";
    }

}

#endif
