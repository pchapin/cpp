
#ifndef OPTION_HPP
#define OPTION_HPP

template<typename T>
class Option {
private:
    T *value;   // nullptr if the Option is empty.

public:
    Option( );                                 // Constructs an empty Option.
    Option( const T &item );                   // Constructs an Option holding a copy of item.
    Option( const Option &other );             // Copy the value (if it exists)
    Option &operator=( const Option &other );  // Copy the value (if it exists)
    Option( Option &&other );
    Option &operator=( Option &&other );
   ~Option( );

    // Extracts the item from the option.
    const T &get( ) const;

    // Applies f to the value in this Option. Returns a (copy of) this Option if f returns
    // true; an empty option otherwise. If this Option is empty and empty Option is returned.
    template<typename Function>
    Option<T> filter( Function f ) const;

    // Applies f to the value in this Option. Returns an Option containing the result of f.
    // If this Option is empty an empty Option is returned.
    template<typename U, typename Function>
    Option<U> transform( Function f ) const;
};

// ====================
// IMPLEMENTATION BELOW
// ====================

template<typename T>
inline
Option<T>::Option( )
{
    value = nullptr;
}


template<typename T>
inline
Option<T>::Option( const T &item )
{
    value = new T( item );
}


template<typename T>
Option<T>::Option( const Option &other )
{
    // If 'other' is empty, make us empty...
    if( other.value == nullptr ) {
        value = nullptr;
    }

    // Otherwise copy 'other's value...
    else {
        value = new T( *other.value );
    }
}


template<typename T>
Option<T> &Option<T>::operator=( const Option &other )
{
    if( this != &other ) {
        delete value;
        value = nullptr;
        if( other.value != nullptr ) {
            value = new T( *other.value );
        }
    }
    return *this;
}


template<typename T>
Option<T>::Option( Option &&other )
{
    // Drain the value out of 'other'.
    value = other.value;
    other.value = nullptr;
}


template<typename T>
Option<T> &Option<T>::operator=( Option &&other )
{
    if( this != &other ) {
        delete value;
        value = other.value;
        other.value = nullptr;
    }
    return *this;
}


template<typename T>
inline
Option<T>::~Option( )
{
    delete value;
}


template<typename T>
inline
const T &Option<T>::get( ) const
{
    return *value;
}


template<typename T>
template<typename Function>
Option<T> Option<T>::filter( Function f ) const
{
    // If I'm empty return a fresh, empty Option.
    if( value == nullptr ) {
        return Option( );
    }
    // If 'f' says "true" about me, return a copy of myself.
    else if( f( *value ) ) {
        return Option( *this );
    }
    // Otherwise 'f' said "false"; return an empty option.
    else {
        return Option( );
    }
}


template<typename T>
template<typename U, typename Function>
Option<U> Option<T>::transform( Function f ) const
{
    // If I'm empty return a fresh, empty Option<U>
    if( value == nullptr ) {
        return Option<U>( );
    }
    // Otherwise return the result of transformation.
    else {
        return Option<U>( f( *value ) );
    }
}

#endif
