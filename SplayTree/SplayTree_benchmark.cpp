/*! \file   SplayTree_benchmark.hpp
 *  \brief  A program that compares the performance of SplayTree against std::set.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <random>
#include <set>
#include <vector>
#include "SplayTree.hpp"

std::vector<int> prepare_random_values( )
{
    std::vector<int> result;

    for( int i = 0; i < 10'000'000; ++i ) {
        result.push_back( i );
    }
    
    // Now shuffle the result vector randomly.
    std::random_device rd;
    std::mt19937 generator( rd( ) );
    std::shuffle( result.begin( ), result.end( ), generator );
    return result;
}

std::vector<int> prepare_sorted_values( )
{
    std::vector<int> result;

    for( int i = 0; i < 10'000'000; ++i ) {
        result.push_back( i );
    }
    return result;
}

template<template<typename...> typename Container>
void insert_test( const std::vector<int> &values )
{
    Container<int> container;

    auto start = std::chrono::high_resolution_clock::now( );
    for( const auto &value : values ) {
        container.insert( value );
    }
    auto end = std::chrono::high_resolution_clock::now( );
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Total time : "
        << elapsed_seconds.count( ) << " seconds" << std::endl;
    std::cout << "Time/insert: "
        << (elapsed_seconds.count( ) * 1.0E6) / values.size( ) << " microseconds" << std::endl;
}

int main( )
{
    std::vector<int> values;

    std::cout << "\n*** Preparing Random Values..." << std::endl;
    values = prepare_random_values( );
    std::cout << "Checking std::set insert..." << std::endl;
    insert_test<std::set>( values );
    std::cout << "Checking spica::SplayTree insert..." << std::endl;
    insert_test<spica::SplayTree>( values );

    std::cout << "\n*** Preparing Sorted Values..." << std::endl;
    values = prepare_sorted_values( );
    std::cout << "Checking std::set insert..." << std::endl;
    insert_test<std::set>( values );
    std::cout << "Checking spica::SplayTree insert..." << std::endl;
    insert_test<spica::SplayTree>( values );

    return EXIT_SUCCESS;
}