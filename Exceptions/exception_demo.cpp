
#include <iostream>

using namespace std;

// Some low level function...
void f( )
{
    // Do stuff...

    // The function detects an error. Instead of returning an error code that must be checked
    // and returned all the way up the call stack, it throws an exception object of some kind.
    // In C++ it is possible to throw any data type, even primitive types like integers
    // (although it is common to define a class for exceptions and throw an instance of that
    // class as is done in Java).
    //
    if( error )
        throw 42;
    // Do more stuff...
}

// Function 'g' does not explicitly throw, nor does it handle any exceptions. If f throws, the
// exception "propagates" through g. The code after the call to f is not executed, BUT
// DESTRUCTORS OF LOCAL OBJECTS WILL BE EXECUTED. This releases any resources used by g,
// regardless of if an exception occurs or not (compare with Java's need to have a 'finally'...
// C++ does not have that feature). This is often called "Resource Acquisition is
// Initialization" or RAI.
//
void g( )
{
    // Do stuff...
    f( );
    // Do more stuff...
}

// Similarly 'h' will just propagate the exception.
void h( )
{
    // Do stuff...
    g( );
    // Do more stuff...
}

int main( )
{
    try {
        // Do stuff...

        // If 'h' throws an exception the rest of the try block is aborted.
        h( );
        // Do more stuff...
    }

    // The type of the exception object thrown is matched at runtime against the types used in
    // the catch clauses (could be multiple catch clauses). If a match is found, the catch
    // clause executes. The program continues after the catch. EXCEPTIONS DO NOT RESUME at the
    // point of the throw. Resumable exceptions were considered for C++, but the idea was
    // rejected as too difficult to use safely and not particularly useful. Few languages have
    // resumable exceptions.
    //
    catch( int ex ) {
        cout << "Caught exception: " << ex << "\n";
    }
    return 0;
}

// A few more notes:
//
// 1. Use exceptions for "exceptional" issues. That is, for issues that should rarely arise. Use
//    other methods of reporting errors (like returning error codes) for "common" errors or for
//    situations that aren't really errors, e. g. failing to open a file because it does not
//    exist.
//
//    It is possible to implement exceptions in C++ such that they incure ZERO overhead in the
//    case where no exception occurs. The price, however, is that there is large overhead to
//    handle the exception. If exceptions are unusual, this is a good thing. Note that it is
//    also possible to implement exceptions in C++ with balanced overhead, but that violates the
//    rule that you shouldn't pay for features you don't use (consider functions 'g' and 'h'
//    above).
//
// 2. In general, exceptions are best at reporting errors over long distances. If you throw an
//    exception and catch it on the next line, something is probably wrong. Exceptions provide a
//    convenient way for a function that detects an error to report that error to a much higher
//    level place where the handling is clear.
//
// 3. The 'new' operator throws an instance of std::bad_alloc when it runs out of memory. The
//    'new' operator never returns the nullptr (in contrast, C's malloc() function returns NULL
//    if it fails to find the memory requested).
//
// 4. "Exception safety" is a big deal, but that subject deserves it's own file!
