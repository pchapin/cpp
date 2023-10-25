
#include <algorithm>
#include <functional>   // Needed for std::less, std::greater, etc.
#include <iostream>
#include <vector>
#include "issorted.hpp"

// using namespace std;

int main( )
{
    std::vector<int> v{ 5, 3, 8, 6, 1, 4, 7, 2, 9, 0 };

    if( vtsu::is_sorted( v.begin( ), v.end( ) ) ) {
        std::cout << "The original array is sorted (WRONG)!" << std::endl;
    }

    // This sort is coming from <algorithm>.
    std::sort( v.begin( ), v.end( ) );

    if( vtsu::is_sorted( v.begin( ), v.end( ) ) ) {
        std::cout << "The array is now sorted!" << std::endl;
    }
}
