
#ifndef STRING_HPP
#define STRING_HPP

#include <cstddef>
#include <iosfwd>

namespace vtc {

    class String {
    public:
        // Default construct a String to an empty value.
        String( );

        // Destroy a String.
       ~String( );

        // Copy constructor.
        String( const String &other );

        // Copy assignment operator.
        String &operator=( const String &other );

        // Copies a C-style string into this String.
        String( const char *other );

        // Move constructor.
        String( String &&other );

        // Move assignment operator.
        String &operator=( String &&other );

        // Return the length of this String.
        std::size_t length( ) const
            { return size; }

        // Give read only access to the text of the string on a per-character basis.
        const char &operator[]( std::size_t index ) const
            { return buffer[index]; }

        // Give read/write access to the text of the string on a per-character basis.
        char &operator[]( std::size_t index )
            { return buffer[index]; }

        // Inserts 'ch' into the string at 'position'. If position is just off the end of the
        // string, this method appends ch onto the string. If position is "far" off the end of
        // the string, there is no effect (no exception is thrown and the program continues
        // normally).
        void insert( std::size_t position, char ch );

    private:
        // INVARIANT: ? One question to ask yourself: should the string include a trailing null
        // character?
        
        // You may add or change the private section as you desire (but be sure the inline
        // methods above still produce the correct results).
        
        char *buffer;
        std::size_t size;
    };


    //! Output a String to the given ostream.
    std::ostream &operator<<( std::ostream &output, const String &s );

}

#endif
