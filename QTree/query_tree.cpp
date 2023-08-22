
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool matching_key_path( const vector<string> &path_components, const string &search_key_path )
{
    string current_key_path;
    for( const auto &path_component : path_components ) {
        current_key_path += "/";
        current_key_path += path_component;
    }
    return current_key_path == search_key_path;
}


void adjust_indentation(
    vector<string>            &path_components,
    vector<string::size_type> &indentation_depths,
    const string              &key,
    string::size_type          indentation_depth )
{
    if( indentation_depth > indentation_depths.back( ) ) {
        // We are going deeper into the tree.
        path_components.push_back( key );
        indentation_depths.push_back( indentation_depth );
    }
    else {
        // We are going up the tree.
        // Note that there is an assumption here that indentation_depth exists in the vector.
        while( indentation_depth < indentation_depths.back( ) ) {
            path_components.pop_back( );
            indentation_depths.pop_back( );
        }
        path_components.back( ) = key;
    }
}


int main( int argc, char *argv[] )
{
    // Verify the number of parameters
    if( argc != 2 ) {
        cerr << "Usage: " << argv[0] << " key-path" << endl;
        return EXIT_FAILURE;
    }

    // For now we will assume the key-path is in the right format.
    // TODO: Add a check for the key-path format.
    string search_key_path{ argv[1] };

    // Open the data file.
    // TODO: Add a way for the data file name to be supplied by the user.
    ifstream data_file{ "data.txt" };

    // Initialize key-path information
    vector<string::size_type> indentation_depths{ 0 };
    vector<string> path_components{ "" };

    // Process the file. For now we will assume the data file is in the right format.
    string line;
    bool done = false;
    while( !done && getline( data_file, line ) ) {

        // TODO: Remove tabs from the line.

        // Remove comments, if any.
        auto comment_start = line.find( '#' );
        if( comment_start != string::npos ) {
            line.erase( comment_start );
        }

        // Strip trailing spaces, if any.
        auto trailing_space_start = line.find_last_not_of( " \r" );
        if( trailing_space_start != string::npos ) {
            line.erase( trailing_space_start + 1 );
        }
        else {
            // The line is all spaces.
            line.clear( );
        }

        // Skip empty lines. Note that this will now include lines that were originally all comments.
        if( line.empty( ) ) {
            continue;
        }

        #ifdef DEBUG
        cout << line << endl;
        #endif

        // Find the indentation depth of the line.
        auto indentation_depth = line.find_first_not_of( " " );
        auto key_end = line.find_first_of( " ", indentation_depth );
        // TODO: Is it okay to subtract a value from string::npos?
        string key{ line.substr( indentation_depth, key_end - indentation_depth ) };

        // Is this a new key at the same indentation depth we've been using?
        if( indentation_depth == indentation_depths.back( ) ) {
            // Replace the last path component with the new key.
            path_components.back( ) = key;
        }
        else {
            // Adjust the indentation depth.
            adjust_indentation( path_components, indentation_depths, key, indentation_depth );
        }

        // Is this the key we want?
        if( matching_key_path( path_components, search_key_path ) ) {
            if( key_end == string::npos ) {
                cout << "*NO VALUE*" << endl;
            }
            else {
                // This assumes extra spaces before the value are part of the value.
                cout << line.substr( key_end + 1 ) << endl;
            }
            done = true;
        }
    }

    return EXIT_SUCCESS;
}
