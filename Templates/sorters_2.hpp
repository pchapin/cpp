
#ifndef SORTERS_HPP
#define SORTERS_HPP

#include <algorithm>
#include <iterator>
#include <functional>

namespace vtsu {

    // A C++ sorting function template. The type parameter is for an iterator type that can be
    // moved forward. More "powerful" iterator types are also allowed, as long as they have at
    // least the abilities required here. In this template first "points" at the first element
    // of the array and last "points" just past the last element of the array.
    //
    #ifdef NEVER
    template<typename ForwardIterator>
    void bubble_sort( ForwardIterator first, ForwardIterator last )
    {
        // We don't want to do 'using namespace std' in a header file. However, for reasons
        // described below, we also don't want to qualify the use of swap with std::. Including
        // a using declaration here (not a using directive!) gives us the effect we want.
        using std::swap;

        if( first == last ) return;

        bool done = false;
        while( !done ) {
            done = true;

            ForwardIterator p1 = first;
            ForwardIterator p2 = first;
            ++p2;

            while( p2 != last ) {
                // Array elements must be comparable with "<". When the compiler specializes
                // this template it will use whatever "<" is appopriate, perhaps inline
                // expanding it here. This greately reduces overhead as compared to the C way of
                // handling generic code shown below.
                if( *p2 < *p1 ) {
                    // Array elements swapped here using, probably, the standard library swap
                    // template. However, if the type being swapped has it's own specialized
                    // swap function, it will be used instead because of overload resolution.
                    // Many types can implement swap much more efficiently than repeated copying
                    // so taking advantage of thier specialized swap functions is very
                    // desirable.
                    swap( *p1, *p2 );
                    done = false;
                }
                ++p1;
                ++p2;
            }
        }
    }
    #endif

    template<typename ForwardIterator, typename Comp>
    void bubble_sort( ForwardIterator first, ForwardIterator last, Comp compare )
    {
        using std::swap;

        if( first == last ) return;

        bool done = false;
        while( !done ) {
            done = true;

            ForwardIterator p1 = first;
            ForwardIterator p2 = first;
            ++p2;

            while( p2 != last ) {
                if( compare( *p2, *p1 ) ) {
                    swap( *p1, *p2 );
                    done = false;
                }
                ++p1;
                ++p2;
            }
        }
    }


    template<typename ForwardIterator>
    void bubble_sort( ForwardIterator first, ForwardIterator last )
    {
        bubble_sort( first, last,
            std::less<typename std::iterator_traits<ForwardIterator>::value_type>( ) );
    }

    // The C way of creating a generic sorting function. Here the array is represented as a blob
    // of raw memory with array_size elements, each element_size bytes. Internally the function
    // computes the location of each element "manually" and uses the provided comparison
    // function to find out their ordering. Such functions are tedious and error-prone to write.
    // They are also less efficient than desired because of the overhead of calling the
    // comparison function indirectly. Finally, they are more difficult to use because the
    // caller has to provide a suitable comparison function.
    //
    void bubble_sort(
        void *first, int array_size, int element_size, int (*compare)(void *, void *) );

}

#endif
