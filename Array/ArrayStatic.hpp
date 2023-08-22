
#ifndef ARRAYSTATIC_HPP
#define ARRAYSTATIC_HPP

#include <stdexcept>

/*!
 * An array-like template where the size is specified by a non-type template parameter. This
 * means ArrayStatic objects with different sizes have different types. It also means the
 * storage managed by the object can be known to the compiler, simplifying many of the methods.
 */
template<typename T, std::size_t n>
class ArrayStatic {
public:
    // Generated default constructor okay?
    // Generated copy constructor is okay.
    // Generated copy assignment operator is okay.
    // Generated destructor is okay.

    const T &operator[]( std::size_t index ) const noexcept;
    T &operator[]( std::size_t index ) noexcept;
    const T &at( std:: size_t index ) const;
    T &at( std::size_t index );

    // Element-by-element comparison.
    bool operator==( const ArrayStatic &other ) const;
    bool operator< ( const ArrayStatic &other ) const;
private:
    // ArrayStatic objects hold the entire array directly.
    T array[n];
};


template<typename T, std::size_t n>
inline const T &ArrayStatic<T, n>::operator[]( std::size_t index ) const noexcept
{
    return array[index];
}


template<typename T, std::size_t n>
inline T &ArrayStatic<T, n>::operator[]( std::size_t index ) noexcept
{
    return array[index];
}


template<typename T, std::size_t n>
const T &ArrayStatic<T, n>::at( std::size_t index ) const
{
    if( index >= n ) {
        throw std::out_of_range( "ArrayStatic<T, n>::at: Index out of range" );
    }
    return array[index];
}


template<typename T, std::size_t n>
T &ArrayStatic<T, n>::at( std::size_t index )
{
    if( index >= n ) {
        throw std::out_of_range( "ArrayStatic<T, n>::at: Index out of range" );
    }
    return array[index];
}


template<typename T, std::size_t n>
bool ArrayStatic<T, n>::operator==( const ArrayStatic &other ) const
{
    for( std::size_t i = 0; i < n; ++i ) {
        if( !(array[i] == other.array[i]) ) return false;
    }
    return true;
}


template<typename T, std::size_t n>
bool ArrayStatic<T, n>::operator<( const ArrayStatic &other ) const
{
    for( std::size_t i = 0; i < n; ++i ) {
        if(   array[i] <  other.array[i]  ) return true;
        if( !(array[i] == other.array[i]) ) return false;
    }
    // ... the arrays are equal.
    return false;
}

// The other four relational operators can be generated from templates in namespace std::rel_ops.

#endif
