/*! \file    main.cpp
 *  \brief   Sample program to illustrate basic usage of C++ 2011 threads.
 *  \author  Peter C. Chapin <pchapin@vtc.edu>
 */

#include <chrono>
#include <cmath>  // C++'s version of C's math.h
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

// Lock associated with shared resource (the console in this case).
mutex console_mutex;

// This class is "callable" because it contains an operator( ). Its state can be used as the
// thread return value. Using a struct is convenient since the data members are already public.
//
struct SquareRoot {
    double result;
    void operator( )( double value );
};

void SquareRoot::operator( )( double value )
{
    // Imagine a much more complicated computation. Store the result in the object's members.
    result = sqrt( value );
}


void output_named_integer( const string &name, const int value )
{
    // This is not exception safe. If an exception in thrown while outputting the result, the
    // mutex is not unlocked.
    //
    //console_mutex.lock( );
    //cout << name << value << endl;
    //console_mutex.unlock( );

    // The destructor of the lock_guard will release the mutex.
    lock_guard<mutex> console_guard( console_mutex );
    cout << name << value << endl;
}

void f( int tick_count )
{
    using namespace chrono_literals;

    for( int i = 1; i <= tick_count; ++i ) {
        output_named_integer( "Tick #", i );
        // Absolute sleep. Thread sleeps until the indicated time.
        this_thread::sleep_until( chrono::high_resolution_clock::now( ) + 1s );
    }
}

void g( int tock_count )
{
    using namespace chrono_literals;
    
    for( int i = 1; i <= tock_count; ++i ) {
        output_named_integer( "Tock #", i );
        // Relative sleep. Thread sleeps for the indicated interval.
        this_thread::sleep_for( 2s );
    }
}

// Demonstrate returning a thread from a function.
thread make_thread( )
{
    // Imagine that the thread arguments are complicated to compute.
    return thread( f, 10 );
}

int main( )
{
    SquareRoot root_computer;

    thread t1 = make_thread( );
    thread t2( g, 5 );
    thread t3( ref( root_computer ), 2.0 );

    // Do other things while the threads work...
    t1.join( );
    t2.join( );
    t3.join( );

    // Print out the results of the square root computation.
    cout << root_computer.result << endl;
    return 0;
}
