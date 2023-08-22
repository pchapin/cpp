
#ifndef ARRAYDYNAMIC_HPP
#define ARRAYDYNAMIC_HPP

#include <cstddef>
#include <memory>
#include <stdexcept>

/*!
 * A fixed size array-like class where the size is set at object construction time
 * (dynamically). This means that two ArrayDynamic objects of different sizes are still
 * considered to have the same type. Assignment of one ArrayDynamic to another requires a
 * runtime check and an exception if the sizes are not compatible. Compare this behavior with
 * that of ArrayStatic.
 */
template<typename T>
class ArrayDynamic {
public:
    ArrayDynamic( std::size_t n );
   ~ArrayDynamic( );

    // Copy operations.
    ArrayDynamic( const ArrayDynamic &other );
    ArrayDynamic &operator=( const ArrayDynamic &other );

    // Move operations
    ArrayDynamic( ArrayDynamic &&other );
    ArrayDynamic &operator=( ArrayDynamic &&other );

    std::size_t size( ) const noexcept
        { return array_size; }

    T &operator[]( size_t index ) noexcept;  // UB if index out of range.
    T &at( size_t index );  // Throws exception if index out of range.

    // The type iterator is an alias for T*. It's full name is ArrayDynamic<T>::iterator. These
    // iterators are really raw pointers and thus in the RandomAccess category.
    typedef T *iterator;

    // Iterator operations.
    iterator begin( ) noexcept
        { return array; }

    iterator end( ) noexcept
        { return array + array_size; }

private:
    T *array;
    std::size_t array_size;
};


template<typename T>
bool operator==( const ArrayDynamic<T> &left, const ArrayDynamic<T> &right )
{
    if( left.size( ) != right.size( ) ) {
        return false;
    }
    for( int i = 0; i < left.size( ); ++i ) {
        if( left[i] != right[i] ) return false;
    }
    return true;
}


template<typename T>
inline bool operator!=( const ArrayDynamic<T> &left, const ArrayDynamic<T> &right )
{
    return !( left == right );
}


template<typename T>
ArrayDynamic<T>::ArrayDynamic( std::size_t n ) :
    array( new T[n] ),
    array_size( n )
{
}


template<typename T>
ArrayDynamic<T>::~ArrayDynamic( )
{
    delete [] array;
}


template<typename T>
ArrayDynamic<T>::ArrayDynamic( const ArrayDynamic &other )
{
    // Notice that this default constructs an array of T...
    std::unique_ptr<T[]> new_copy( new T[other.array_size] );
    for( size_t i = 0; i < other.array_size; ++i ) {
        // ... and here uses operator=() for type T.
        new_copy.get( )[i] = other.array[i];
    }
    // It would be better to copy construct the Ts because:
    //   a) Type T would not need to be default constructable.
    //   b) It's faster (no default construction and no copy assignment of Ts).

    // A unique_ptr is needed because an exception might be thrown while copying the Ts, and we
    // need to be sure the memory pointed at by new_copy is properly released.

    array = new_copy.release( );
    array_size = other.array_size;
}


template<typename T>
ArrayDynamic<T> &ArrayDynamic<T>::operator=( const ArrayDynamic &other )
{
    if( this != &other ) {
        if( array_size != other.array_size ) {
            throw std::runtime_error( "ArrayDynamic<T>::operator=: Incompatible lengths" );
        }
        else {
            std::unique_ptr<T[]> new_copy( new T[other.array_size] );
            for( size_t i = 0; i < other.array_size; ++i ) {
                new_copy.get( )[i] = other.array[i];
            }

            // The copy was successful. Remove the value of the this object...
            if( array != nullptr )
                delete [] array;

            // ... and install the new value.
            array = new_copy.release( );
            array_size = other.array_size;
        }
    }
    return *this;
}


template<typename T>
ArrayDynamic<T>::ArrayDynamic( ArrayDynamic &&other ) :
    array( other.array ),
    array_size( other.array_size )
{
    other.array = nullptr;
    other.array_size = 0;  // Not necessary, but what the heck?
}


template<typename T>
ArrayDynamic<T> &ArrayDynamic<T>::operator=( ArrayDynamic &&other )
{
    if( this != &other ) {
        // It shouldn't be possible to change the size of an object even with a move. Yes?
        if( array_size != other.array_size ) {
            throw std::runtime_error( "ArrayDynamic<T>::operator=: Incompatible lengths" );
        }
        else {
            // Remove the value of this object...
            if( array != nullptr )
                delete [] array;

            // ... and move the other object's value over.
            array = other.array;
            array_size = other.array_size;
            other.array = nullptr;
            other.array_size = 0;  // Not necessary, but what the heck?
        }
    }
    return *this;
}


template<typename T>
T &ArrayDynamic<T>::operator[]( size_t index ) noexcept
{
    return array[index];
}


template<typename T>
T &ArrayDynamic<T>::at( size_t index )
{
    if( index >= array_size ) {
        throw std::out_of_range( "ArrayDynamic<T>::at: Index out of range" );
    }
    return array[index];
}

#endif
