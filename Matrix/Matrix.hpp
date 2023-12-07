/*! \file   Matrix.hpp
 *  \brief  A class for representing matrices of floating point values.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <algorithm>
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
         * In general once a Matrix has been created, its size cannot be changed (although the
         * values of the elements can be).
         *
         * \param incoming_row_count The number of rows in the Matrix.
         * \param incoming_column_count The number of columns in the Matrix.
         *
         * \throws InvalidSize if either incoming_row_count or incoming_column_count is zero.
         */
        Matrix( index_type incoming_row_count, index_type incoming_column_count );

        //! Initializer list constructor.
        /*!
         * This constructor allows a Matrix to be initialized using an initializer list of
         * initializer lists. The outer initializer list represents the rows of the Matrix, and
         * the inner initializer lists represent the columns of a particular row. If the length
         * of the rows differs, the Matrix uses the length of the longest row and pads the
         * shorter rows with zeros (default constructed Ts).
         *
         * \throws InvalidSize if the number of rows is zero or if all of the rows have zero
         * length.
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
        [[nodiscard]] index_type rows( ) const
        { return row_count; }

        [[nodiscard]] index_type columns( ) const
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
        [[nodiscard]] T operator()( index_type row, index_type column ) const;

        //! Read/Write access to a matrix element.
        /*!
         * e.g.:
         *
         * Matrix<double> m{ 2, 5 };
         * m(1, 4) = 3.14159;  // Write to value in lower right corner.
         *
         * \throws OutOfBoundsIndex if either index is out of bounds.
         */
        [[nodiscard]] T &operator()( index_type row, index_type column );

        // Matrix math. Throws InvalidSize if incompatible matrix dimensions are used.
        Matrix &operator+=( const Matrix &other );
        Matrix &operator-=( const Matrix &other );
        Matrix &operator*=( const Matrix &other );

        // Relational operator. C++ 2020 automatically defines operator!= in terms of operator==.
        bool operator==( const Matrix &other ) const;

    private:
        index_type row_count;
        index_type column_count;

        // The intent is for the data to be stored in row major order.
        T *elements;
    };

    // Free Functions
    // ==============

    template<typename T>
    [[nodiscard]] inline Matrix<T> operator+( const Matrix<T> &left, const Matrix<T> &right )
    {
        Matrix<T> temp{ left };
        temp += right;
        return temp;
    }

    template<typename T>
    [[nodiscard]] inline Matrix<T> operator-( const Matrix<T> &left, const Matrix<T> &right )
    {
        Matrix<T> temp{ left };
        temp -= right;
        return temp;
    }

    template<typename T>
    [[nodiscard]] inline Matrix<T> operator*( const Matrix<T> &left, const Matrix<T> &right )
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
        for( typename Matrix<T>::index_type i = 0; i < m.rows( ); ++i ) {
            output << "  [ ";
            for( typename Matrix<T>::index_type j = 0; j < m.columns( ); ++j ) {
                const char *column_terminator = ( j < m.columns( ) - 1 ) ? ", " : " ";
                output << m( i, j ) << column_terminator;
            }

            const char *row_terminator = ( i < m.rows( ) - 1 ) ? "],\n" : "]\n";
            output << row_terminator;
        }
        output << "]\n";
        return output;
    }

    // Matrix Implementation
    // =====================

    template<typename T>
    Matrix<T>::Matrix( index_type incoming_row_count, index_type incoming_column_count ) :
        row_count( incoming_row_count ), column_count( incoming_column_count ), elements( nullptr )
    {
        if( row_count == 0 || column_count == 0 ) {
            throw InvalidSize( "Matrix must have non-zero size" );
        }

        elements = new T[row_count * column_count];
        std::fill( elements, elements + row_count * column_count, T{ } );
    }


    template<typename T>
    Matrix<T>::Matrix( std::initializer_list<std::initializer_list<T>> init_list ) :
        row_count( init_list.size( ) ), column_count( 0 ), elements( nullptr )
    {
        if( row_count == 0 ) {
            throw InvalidSize( "Matrix must have non-zero size" );
        }

        // Find the maximum number of columns in the initializer list.
        for( const auto &row : init_list ) {
            if( row.size( ) > column_count ) {
                column_count = row.size( );
            }
        }
        if( column_count == 0 ) {
            throw InvalidSize( "Matrix must have non-zero size" );
        }

        // Allocate the elements array.
        elements = new T[row_count * column_count];
        std::fill( elements, elements + row_count * column_count, T{ } );

        // Copy the initializer list into the elements array.
        index_type row_index = 0;
        for( const auto &row : init_list ) {
            index_type column_index = 0;
            for( const auto &element : row ) {
                elements[row_index * column_count + column_index] = element;
                ++column_index;
            }
            ++row_index;
        }
    }


    template<typename T>
    Matrix<T>::~Matrix( )
    {
        delete[] elements;
    }


    template<typename T>
    Matrix<T>::Matrix( const Matrix &other ) :
        row_count( other.row_count ), column_count( other.column_count ), elements( nullptr )
    {
        elements = new T[row_count * column_count];
        std::copy( other.elements, other.elements + row_count * column_count, elements );
    }


    template<typename T>
    Matrix<T> &Matrix<T>::operator=( const Matrix &other )
    {
        if( this != &other ) {
            // Try the allocation first. Note that it is theoretically possible for there to be
            // an exception thrown during the std::copy if the type T is something complicated.
            // If that happens, we will leak memory. A std::unique_ptr would be a better choice
            // here.
            //
            T *temp_elements = new T[other.row_count * other.column_count];
            std::copy( other.elements, other.elements + other.row_count * other.column_count, temp_elements );

            // If the above happened without exception, we can commit to the new value.
            delete [] elements;
            elements = temp_elements;
            row_count = other.row_count;
            column_count = other.column_count;
        }
        return *this;
    }


    template<typename T>
    Matrix<T>::Matrix( Matrix &&other ) :
        row_count( other.row_count ), column_count( other.column_count ), elements( other.elements )
    {
        other.elements = nullptr;
        other.row_count = 0;
        other.column_count = 0;
    }


    template<typename T>
    Matrix<T> &Matrix<T>::operator=( Matrix &&other )
    {
        if( this != &other ) {
            delete [] elements;
            elements = other.elements;
            row_count = other.row_count;
            column_count = other.column_count;

            other.elements = nullptr;
            other.row_count = 0;
            other.column_count = 0;
        }
        return *this;
    }


    template<typename T>
    T Matrix<T>::operator()( index_type row, index_type column ) const
    {
        if( row >= row_count || column >= column_count ) {
            throw OutOfBoundsIndex( "Matrix index out of bounds" );
        }
        return elements[row * column_count + column];
    }


    template<typename T>
    T &Matrix<T>::operator()( index_type row, index_type column )
    {
        if( row >= row_count || column >= column_count ) {
            throw OutOfBoundsIndex( "Matrix index out of bounds" );
        }
        return elements[row * column_count + column];
    }


    template<typename T>
    Matrix<T> &Matrix<T>::operator+=( const Matrix &other )
    {
        if( row_count != other.row_count || column_count != other.column_count ) {
            throw InvalidSize( "Matrix dimensions must match in addition" );
        }

        for( index_type i = 0; i < row_count; ++i ) {
            for( index_type j = 0; j < column_count; ++j ) {
                elements[i * column_count + j] += other.elements[i * column_count + j];
            }
        }
        return *this;
    }


    template<typename T>
    Matrix<T> &Matrix<T>::operator-=( const Matrix &other )
    {
        if( row_count != other.row_count || column_count != other.column_count ) {
            throw InvalidSize( "Matrix dimensions must match in subtraction" );
        }

        for( index_type i = 0; i < row_count; ++i ) {
            for( index_type j = 0; j < column_count; ++j ) {
                elements[i * column_count + j] -= other.elements[i * column_count + j];
            }
        }
        return *this;
    }


    template<typename T>
    Matrix<T> &Matrix<T>::operator*=( const Matrix &other )
    {
        if( column_count != other.row_count ) {
            throw InvalidSize( "Incompatible Matrix dimensions in multiplication" );
        }

        // Create a temporary matrix to hold the result.
        Matrix<T> temp{ row_count, other.column_count };

        // Compute the result.
        for( index_type i = 0; i < row_count; ++i ) {
            for( index_type j = 0; j < other.column_count; ++j ) {
                for( index_type k = 0; k < column_count; ++k ) {
                    temp.elements[i * other.column_count + j] +=
                        elements[i * column_count + k] * other.elements[k * other.column_count + j];
                }
            }
        }

        // Commit the result.
        *this = std::move( temp );
        return *this;
    }


    template<typename T>
    bool Matrix<T>::operator==( const Matrix &other ) const
    {
        if( row_count != other.row_count || column_count != other.column_count ) {
            return false;
        }

        for( index_type i = 0; i < row_count; ++i ) {
            for( index_type j = 0; j < column_count; ++j ) {
                if( elements[i * column_count + j] != other.elements[i * column_count + j] ) {
                    return false;
                }
            }
        }
        return true;
    }
}

#endif
