/*! \file    Sieve.cpp
 *  \brief   Sample program to demonstrate futures and promises.
 *  \author  Peter Chapin <pchapin@vermontstate.edu>
 */

#include <chrono>
#include <iostream>
#include <mutex>
#include <future>

// Lock associated with shared resource (the boolean array). This is currently not used, but it
// could be used to protect the array from concurrent access in a future version of this
// program.
std::mutex prime_mutex;

constexpr std::size_t ARRAY_SIZE = 1'000'000'000;
bool prime_array[ARRAY_SIZE + 1];

// This implementation is a modified version of the Sieve of Eratosthenes algorithm found at
// https://www.geeksforgeeks.org/sieve-of-eratosthenes/.
void SieveOfEratosthenes( ) 
{ 
    for( std::size_t i = 0; i <= ARRAY_SIZE; ++i ) {
        prime_array[i] = true;
    }
  
    for( std::size_t p = 2; p * p <= ARRAY_SIZE; p++ ) { 
        // If prime[p] is not changed, then it is a prime. 
        if( prime_array[p] ) { 
            // Update all multiples of p greater than or equal to the square of it. Numbers
            // which are multiple of p and are less than p^2 are already been marked. 
            for( std::size_t i = p * p; i <= ARRAY_SIZE; i += p ) 
                prime_array[i] = false; 
        } 
    } 
}

std::size_t count_primes( )
{
    std::size_t prime_count = 0;
    for( std::size_t i = 2; i <= ARRAY_SIZE; ++i ) {
        if( prime_array[i] ) ++prime_count;
    }
    return prime_count;
}

int main( )
{
    std::future<void> sieve_future = std::async( std::launch::async, SieveOfEratosthenes );
    while( sieve_future.wait_for( std::chrono::seconds( 1 ) ) != std::future_status::ready ) {
        std::cout << "." << std::flush;
    }
    std::cout << std::endl;
    std::cout << "There are " << count_primes( ) << " primes less than or equal to "
              << ARRAY_SIZE << std::endl;
     return 0;
}
