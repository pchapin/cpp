/****************************************************************************
FILE          : d_scanner.cpp
LAST REVISION : 2007-09-08
SUBJECT       : Implementation of a directory scanner class
PROGRAMMER    : (C) Copyright 2007 by Peter C. Chapin

Please send comments or bug reports to

     Peter C. Chapin
     Electrical and Computer Engineering Technology
     Vermont Technical College
     Randolph Center, VT 05061
     Peter.Chapin@vtc.vsc.edu
****************************************************************************/

#include <cstring>
#include "d_scanner.h"

using namespace std;

D_Scanner::D_Scanner( char *directory_name )
{
    char workspace[1024];

    strcpy( workspace, directory_name );
    strcat( workspace, "\\*.*" );

    scan_handle = FindFirstFile( workspace, &scan_information );
    if( scan_handle == INVALID_HANDLE_VALUE )
        info_valid = FALSE;
    else
        info_valid = TRUE;
}


bool D_Scanner::has_more( )
{
    if( info_valid == FALSE ) return false;
    return true;
}


void D_Scanner::next( )
{
    if( scan_handle == INVALID_HANDLE_VALUE ) return;
    info_valid = FindNextFile( scan_handle, &scan_information );
}


void D_Scanner::close( )
{
    if( scan_handle == INVALID_HANDLE_VALUE ) return;
    FindClose( scan_handle );
}

