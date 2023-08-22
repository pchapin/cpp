
#include <cstring>
#include <iostream>
#include "String.hpp"

using namespace std;

namespace vtc {

    String::String( )
    {
        buffer = new char[1];
        buffer[0] = '\0';
        size = 0;
    }


    String::String( const String &other )
    {
        // Copy the other value into *this.
        buffer = new char[other.size + 1];
        strcpy( buffer, other.buffer );
        size = other.size;
    }


    String &String::operator=( const String &other )
    {
        if( this != &other ) {
            // First, allocate the new space.
            char *temp = new char[other.size + 1];

            // Now remove the old value of *this.
            delete [] buffer;

            // Finally, copy the other value into *this.
            buffer = temp;
            strcpy( buffer, other.buffer );
            size = other.size;
        }
        return *this;
    }


    String::~String( )
    {
        delete [] buffer;
    }


    String::String( const char *other )
    {
        buffer = new char[strlen( other ) + 1];
        strcpy( buffer, other );
        size = strlen( other );
    }


    ostream &operator<<( ostream &output, const String &s )
    {
        for( size_t i = 0; i < s.length( ); ++i ) {
            output << s[i];
        }
        return output;
    }

}
