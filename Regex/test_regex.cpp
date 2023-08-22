
#include <cstdlib>
#include <iostream>
#include <boost/regex.hpp>
#include <string>

using namespace std;

int main( )
{
    string line;
    boost::regex  pattern { R"((\d{3})-(\d{4}))" };

    while( getline( cin, line ) ) {
        boost::smatch matches;
        cout << line << "\n";
        if( boost::regex_search( line, matches, pattern ) ) {
            cout << "Match found: " << matches[0]
                 << ", parts: " << matches[1] << " and " << matches[2] << "\n";
        }
    }
    return EXIT_SUCCESS;
}
