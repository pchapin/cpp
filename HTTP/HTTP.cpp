
// C++ standard library.
#include <cstring>
#include <string>

// System specific library.
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "HTTP.hpp"

using namespace std;

//=========================
//     Private Methods
//=========================

void HTTP::establish_connection( )
{
    struct sockaddr_in server_address;

    // Look up the IP address associated with the given host name.
    struct hostent *host_information = gethostbyname( host_name.c_str( ) );
    if( host_information == nullptr ) return;

    // Fill in the socket address structure.
    // TODO: Make sure the given port number is in a sensible range.
    memset( &server_address, 0, sizeof( server_address ) );
    server_address.sin_family = AF_INET;
    server_address.sin_port   = htons( static_cast<uint16_t>( port_number ) );
    memcpy( &server_address.sin_addr.s_addr, host_information->h_addr_list[0], 4 );

    // Create a socket object in the kernel.
    socket_handle = socket( PF_INET, SOCK_STREAM, 0 );
    if( socket_handle == -1 ) return;

    // Create a connection with the server.
    if( connect( socket_handle, (struct sockaddr *)&server_address, sizeof(server_address) ) < 0 ) {
        close(socket_handle);
        socket_handle = -1;
    }
}

//========================
//     Public Methods
//========================

HTTP::HTTP( const string &host, int port ) :
    host_name( host ),
    port_number( port ),
    socket_handle( -1 )
{
    establish_connection( );
}


HTTP::~HTTP( )
{
    if( socket_handle != -1 ) {
        close( socket_handle );
    }
}


// Copy constructor.
// FINISH ME!

// Copy assignment first cleans up *this and then copies the existing connection.
// FINISH ME!

// Move constructor "drains" the existing object.
// FINISH ME!

// Move assignment "drains the existing object after cleaning up *this.
// FINISH ME!

string HTTP::get( const string &absolute_path )
{
    const int buffer_size = 1024;

    char buffer[buffer_size];
    int  count;
    string result;

    if( socket_handle == -1 ) {
        return "not connected";
    }
    else {
        // Send GET command.
        string request_message( "GET " );
        request_message += absolute_path;
        request_message += " HTTP/1.0\r\n\r\n";
        // TODO: Check if the write is successful. Throw an exception if it is not.
        write( socket_handle, request_message.c_str( ), request_message.length( ) );

        // Retrieve result.
        while ((count = read( socket_handle, buffer, buffer_size )) > 0) {
            result.append( buffer, count );
        }
        return result;
    }
}
