/*! \file   word_count.cpp
 *  \brief  A simple program counts words in the text at its standard input.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 *
 * This program reads a text file at its standard input and counts the number of times each word
 * appears in the text. It then prints the results to standard output.
 */

#include <algorithm>  // Needed for sort.
#include <cstdlib>    // Needed for EXIT_SUCCESS.
#include <cctype>     // Needed for tolower and isalpha.
#include <iomanip>    // Needed for setw.
#include <iostream>   // Needed for cin, cout, and endl.
#include <map>        // Needed for map.
#include <sstream>    // Needed for istringstream.
#include <string>     // Needed for string.
#include <utility>    // Needed for pair.
#include <vector>     // Needed for vector.

using namespace std;

int main( )
{
    string line;
    string word;
    map<string, unsigned long> word_counts;

    while( getline( cin, line ) ) {

        // Force all letters to lowercase and replace all non-alphabetic characters with spaces.
        for( auto &ch : line ) {
            ch = tolower( ch );
            if( !isalpha( ch ) ) ch = ' ';
        }

        // Extract all the words from this line and count them.
        istringstream line_stream{ line };
        while( line_stream >> word ) {
            if( word_counts.count( word ) == 0 ) {
                word_counts[word] = 1;
            }
            else {
                ++word_counts[word];
            }
        }
    }

    // I want to sort the results by the counts. To do that I need to copy the map into a vector
    // of pairs. I can then sort the vector. Note that I'm using a stable sort so that words
    // with the same count will be sorted alphabetically. This takes advantage of the fact that
    // the keys in a map are sorted.
    //
    vector<pair<string, unsigned long>> word_counts_vector{ begin( word_counts ), end( word_counts ) };
    stable_sort( begin( word_counts_vector ), end( word_counts_vector ),
          []( const auto &left, const auto &right ) {
              return left.second > right.second;
          } );

    // Finally, display the words and their corresponding counts.
    for( const auto &item : word_counts_vector ) {
        cout << setw(16) << item.first << " " << item.second << endl;
    }

    return EXIT_SUCCESS;
}