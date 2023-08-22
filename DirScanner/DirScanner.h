/****************************************************************************
FILE          : d_scanner.h
LAST REVISION : 2007-09-08
SUBJECT       : Interface to a directory scanner class
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#ifndef D_SCANNER_H
#define D_SCANNER_H

#include <windows.h>

class D_Scanner {
    public:
        // Sets the directory to scan.
        D_Scanner( char *directory_name );

        // Returns true if there are more files to return.
        bool has_more( );

        // Returns a pointer to the file's name (no path).
        char *get( )
            { return( scan_information.cFileName ); }

        // Advances to the next name in the directory.
        void next( );

        // Call this method when the scan is done to clean up.
        void close( );

    private:
        HANDLE          scan_handle;
        WIN32_FIND_DATA scan_information;
        BOOL            info_valid;
};

#endif

