
#ifndef SORTERS_HPP
#define SORTERS_HPP

#include <algorithm>

namespace vtsu {

    // A non-generic version of the bubble_sort algorithm.
    
    // NOTE: The body of this function should really be in a .cpp file. For this reason, it is
    // compiled out here.
    #ifdef NEVER
    void bubble_sort_1( int *first, int *last )
    {
        if( first == last ) return;

        bool done = false;
        while( !done ) {
            done = true;

            int *p1 = first;
            int *p2 = first + 1;

            while( p2 != last ) {
                if( *p2 < *p1 ) {
                    std::swap( *p1, *p2 );
                    done = false;
                }
                ++p1;
                ++p2;
            }
        }
    
    }
    #endif

    // A generic version that allows sorting of any array with an element type has an operator<

    template<typename T>
    void bubble_sort_2( T *first, T *last )
    {
        if( first == last ) return;

        bool done = false;
        while( !done ) {
            done = true;

            T *p1 = first;
            T *p2 = first + 1;

            while( p2 != last ) {
                if( *p2 < *p1 ) {
                    std::swap( *p1, *p2 );
                    done = false;
                }
                ++p1;
                ++p2;
            }
        }
    
    }


    // An attempt to generalize to any sequence.

    template<typename ForwardIterator>
    void bubble_sort_3( ForwardIterator first, ForwardIterator last )
    {
        if( first == last ) return;

        bool done = false;
        while( !done ) {
            done = true;

            ForwardIterator p1 = first;
            ForwardIterator p2 = first;
            ++p2;
            
            while( p2 != last ) {
                if( *p2 < *p1 ) {
                    std::swap( *p1, *p2 );
                    done = false;
                }
                ++p1;
                ++p2;
            }
        }
        
    }

    // Iterator categories.

    // "Random Access" iterators (like normal pointers).
    // "Bidirectional" iterators (no "jumping" but do allow forward/backward motion).
    // "Forward" iterators (only goes forward, but allows multiple passes).
    // "Input" iterators (read only) and "Output" iterators (write only) also only one pass.

}

#endif
