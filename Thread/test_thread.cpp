
#include <cstdlib>
#include <iostream>
#include <string>
#include <boost/thread.hpp>

using namespace std;

void f( const string &message )
{
    string line;
    while( getline( cin, line ) ) {
        cout << message << ": " << line << "\n";
    }
}

int main( )
{
    boost::thread worker { f, "worker" };
    worker.join( );
    return EXIT_SUCCESS;
}
