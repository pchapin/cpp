
#include <algorithm>
#include <vector>
#include "issorted.hpp"

using namespace std;

int main( )
{
    vector<int> v = { 5, 3, 8, 1, 2, 9, 0 };

    if( is_sorted( v.begin( ), v.end( ) ) ) {
        cout << "It didn't work!\n";
    }

    sort( v.begin( ), v.end( ) );

    if( is_sorted( v.begin( ), v.end( ) ) ) {
        cout << "It worked!\n";
    }
}
