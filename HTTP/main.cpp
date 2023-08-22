
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "HTTP.hpp"

using namespace std;

// Duplicates a connection 'count' times and returns a vector with all the connections.
vector<HTTP> make_multiple( const HTTP &primary, int count )
{
    vector<HTTP> connections;

    for( int i = 0; i < count; ++i ) {
        connections.push_back( primary );
    }
    return connections;
}

int main( )
{
    int count = 0;

    // Connect to some unsuspecting web server.
    HTTP primary_connection( "www.cis.vtc.edu" );

    // Give me five more connections to that server, please.
    vector<HTTP> connection_vector( make_multiple( primary_connection, 5 ) );

    // Let's get some web pages!
    for( HTTP &connection : connection_vector ) {
        cout << "==========> " << ++count << "\n";
        string page = connection.get( "/" );
        cout << page << "\n";
    }

    // Whoa... did we close those connections? You bet we did!
    return EXIT_SUCCESS;
}
