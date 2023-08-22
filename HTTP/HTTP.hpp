
#ifndef HTTP_HPP
#define HTTP_HPP

#include <string>

class HTTP {
public:
    // Connects to the web server on the indicated host at the indicated port.
    HTTP( const std::string &host, int port = 80 );

    // Closes the connection to the server.
   ~HTTP( );

    // Copy/move management...
    // FINISH ME!

    // Uses the HTTP GET method to retrieve a path on the server.
    std::string get( const std::string &absolute_path );

private:
    std::string host_name; // The host to which we are connected.
    int port_number;       // The remote port number we are using.
    int socket_handle;     // -1 means not connected.

    // Connects to the current host/port. Note: Only call if socket_handle is not connected!
    // TODO: Deal with errors!
    void establish_connection( );
};

#endif
