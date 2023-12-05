/*! \file    Thread_demo.cpp
 *  \brief   Sample program to illustrate basic usage of C++ 2011 threads.
 *  \author  Peter Chapin <pchapin@vermontstate.edu>
 */

#include <chrono>
#include <cmath>
#include <iostream>
#include <mutex>
#include <thread>

// Lock associated with shared resource (the console in this case).
std::mutex console_mutex;

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
    result = std::sqrt( value );
}


void output_named_integer( const std::string &name, const int value )
{
    // The commented code is not exception safe. If an exception in thrown while outputting the
    // result, the mutex is not unlocked.
    //
    //console_mutex.lock( );
    //cout << name << value << endl;
    //console_mutex.unlock( );

    // The destructor of the lock_guard will release the mutex.
    std::lock_guard<std::mutex> console_guard( console_mutex );
    std::cout << name << value << std::endl;
}

void do_tick( int tick_count )
{
    using namespace std::chrono_literals;

    for( int i = 1; i <= tick_count; ++i ) {
        output_named_integer( "Tick #", i );
        // Absolute sleep. Thread sleeps until the indicated time.
        std::this_thread::sleep_until( std::chrono::high_resolution_clock::now( ) + 1s );
    }
}

void do_tock( int tock_count )
{
    using namespace std::chrono_literals;
    
    for( int i = 1; i <= tock_count; ++i ) {
        output_named_integer( "Tock #", i );
        // Relative sleep. Thread sleeps for the indicated interval.
        std::this_thread::sleep_for( 2s );
    }
}

// Demonstrate returning a thread from a function.
std::thread make_thread( )
{
    // Imagine that the thread arguments are complicated to compute.
    return std::thread( do_tick, 10 );
}

int main( )
{
    SquareRoot root_computer;

    std::thread t1 = make_thread( );   // Does Tick 10 times (1 second apart)
    std::thread t2( do_tock, 5 );      // Does Tock 5 times (2 seconds apart)
    std::thread t3( std::ref( root_computer ), 2.0 );

    // Do other things here while the threads work.

    // Wait for the threads to finish.
    t1.join( );
    t2.join( );
    t3.join( );

    // Print the results of the square root computation.
    std::cout << root_computer.result << std::endl;
    return 0;
}
