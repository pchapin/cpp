/*! \file    bubble_sort.hpp
 *  \brief   A generic implementation of bubble sort.
 *  \author  Peter Chapin <peter.chapin@vermontstate.edu>
 * 
 * This file is used in CIS-3012, the C++ Programming class at Vermont State University.
 */

#ifndef SORTERS_HPP
#define SORTERS_HPP

#include <algorithm>    // Needed for std::swap
#include <iterator>     // Needed for std::iterator_traits
#include <functional>   // Needed for std::less

// BP: If you want to comment out a block of code, it is better to use conditional compilation
// directives instead of /* ... */ comments. The problem with /* ... */ comments is that they do
// not nest. If you have a /* ... */ comment inside another /* ... */ comment, the compiler will
// complain. Conditional compilation directives do nest and are therefore more flexible. They
// also have the advantage that they can be used to conditionally compile out code that is
// incorrect, which can be useful during development if you want to test some code before you've
// finished other sections.
//
// The use of the symbol NEVER is conventional. Just remember to "never say never!"
#ifdef NEVER

// A non-generic version of the bubble_sort algorithm that only works on arrays of int.
//
// NOTE: The body of this function should be in a .cpp file which is why it conditionally
// compiled out. It is included here for reference.
void bubble_sort( int *first, int *last )
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
            p1++;
            p2++;
        }
    }
}
#endif

//! Sorts a sequence using the BubbleSort algorithm.
/*!
 * This algorithm sorts a sequence delimited by two forward iterators [first, last). The sorting
 * is done in place. The comparison function is used to determine the ordering of the elements.
 * The comparison function should return true if the first argument is less than (i.e., comes
 * before) the second argument. Otherwise it should return false. Note that the comparison
 * function can be any function-like (i.e., callable) object. This includes function pointers,
 * functors, and lambda expressions.
 * 
 * \tparam ForwardIterator The type of iterator used to access the sequence to be sorted.
 * \tparam Comp            The type of the comparison function used to compare elements.
 * \param first An iterator that points at the first element of the sequence to be sorted.
 * \param last  An iterator that points just past the last element of the sequence to be sorted.
 */
template<typename ForwardIterator, typename Comp>
void bubble_sort( ForwardIterator first, ForwardIterator last, Comp compare )
{
    // We don't want to do 'using namespace std' in a header file. However, for reasons
    // described below, we also don't want to qualify the use of swap with std::. Including a
    // using declaration here (not a using directive!) gives us the effect we want.
    using std::swap;

    if( first == last ) return;

    bool done = false;
    while( !done ) {
        done = true;

        ForwardIterator p1 = first;
        ForwardIterator p2 = first;
        p2++;

        while( p2 != last ) {

            // Here we use the comparison object to check the order.
            if( compare( *p2, *p1 ) ) {

                // Array elements swapped here using, probably, the standard library swap
                // template. However, if the type being swapped has it's own specialized swap
                // function, it will be used instead because of the way overload resolution
                // works. Many types can implement swap much more efficiently than repeated
                // copying so taking advantage of their specialized swap functions is very
                // desirable. For example, std::string has a specialized swap function that
                // swaps the internal pointers of the two strings; it does not copy the strings.
                swap( *p1, *p2 );
                done = false;
            }
            p1++;
            p2++;
        }
    }
}

// A convenience template that uses the less-than operator to compare elements. It works by
// passing the std::less functor to the more general bubble_sort template above. To do this, it
// needs to know the type of the elements being sorted. This is determined by looking at the
// value_type member of the iterator using the iterator_traits template. This is a C++ 1998 way
// of doing things.
template<typename ForwardIterator>
void bubble_sort( ForwardIterator first, ForwardIterator last )
{
    bubble_sort( first, last,
        std::less<typename std::iterator_traits<ForwardIterator>::value_type>( ) );
}

// The C way of creating a generic sorting function. Here the array is represented as a blob of
// raw memory with `array_size` elements, each `element_size` bytes in size. Internally, the
// function computes the location of each element "manually" and uses the provided comparison
// function to find out their ordering. Such functions are tedious and error-prone to write.
// They are also less efficient than desired because of the overhead of calling the comparison
// function indirectly. Finally, they are more difficult to use because the caller has to
// provide a suitable comparison function, which is awkward in C.
void bubble_sort(
    void *first, int array_size, int element_size, int (*compare)(void *, void *) );

#endif
