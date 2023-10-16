
#ifndef VTSU_SORTERS_HPP
#define VTSU_SORTERS_HPP

#include <algorithm>    // Needed for std::swap.
#include <iterator>     // Needed for std::iterator_traits.
#include <functional>   // Needed for std::less.

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


    // A generic version that allows sorting of any array with an element type has an
    // `operator<`. This version assumes the sequence to be sorted is an array. We will further
    // generalize this below.

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


    // This version generalizes the sorting algorithm to work on any sequence of elements that
    // supports forward iterators. Note that the name of the type parameter, `ForwardInteger`,
    // is not really significant. It only serves as documentation. The fact that only forward
    // iterators are required, and not some more powerful iterator type, is manifest in the
    // operations that are used on objects of type `ForwardIterator`.

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


    // This version further generalizes the algorithm to allow the use of a user-supplied
    // comparison object. This is useful when the elements of the sequence to be sorted do not
    // have an `operator<` defined for them or when the user wants to sort the elements in some
    // order other than ascending. 

    template<typename ForwardIterator, typename Comparison>
    void bubble_sort( ForwardIterator first, ForwardIterator last, Comparison compare )
    {
        // We don't want to do 'using namespace std' in a header file. However, for reasons
        // described below, we also don't want to qualify the use of swap with std::. Including
        // a using declaration here (not a using directive!) gives us the effect we want.
        //
        // Note that the scope of the using declaration is limited to the function body. 
        using std::swap;

        if( first == last ) return;

        bool done = false;
        while( !done ) {
            done = true;

            ForwardIterator p1 = first;
            ForwardIterator p2 = first;
            ++p2;

            while( p2 != last ) {

                // The comparison object is used to define the sort order. It returns `true` if
                // the first argument "comes before" the second argument in the desired order.
                // It is up to the user to provide a suitable comparison object.
                if( compare( *p2, *p1 ) ) {

                    // Sequence elements are swapped here using, probably, the standard library
                    // swap template, due to the using directive above. However, if the type
                    // being swapped has it's own specialized swap function, it will be used
                    // instead, because of overload resolution (an explicitly declared function
                    // is used in preference to specializing a template). Many types can
                    // implement swap much more efficiently than repeated copying, which is what
                    // `std::swap` does, so taking advantage of their specialized swap functions
                    // is very desirable.
                    swap( *p1, *p2 );
                    done = false;
                }
                ++p1;
                ++p2;
            }
        }
    }

    // The following version of bubble_sort is a wrapper around the previous version. It
    // provides a default comparison object, which is the standard library `less` function
    // object. This allows the user to call bubble_sort with only two arguments, provided the
    // user is content to sort in ascending order and the type `T` has a suitable `operator<`.
    
    template<typename ForwardIterator>
    inline void bubble_sort( ForwardIterator first, ForwardIterator last )
    {
        // Note that `std::less` has no data members. It only has an overloaded `operator()`
        // that allows an object of type `std::less` to be treated like a function. In particular:
        //
        //    std::less<int> less_than;
        //    bool result = less_than( 1, 2 );  // Really less_than.operator()( 1, 2 );
        //
        // Here `result` is `true` because `1` is less than `2`.
        //
        // In the code below, the comparison object is constructed in place using an explicit
        // call to the constructor. The resulting comparison object is then passed into the
        // previous `bubble_sort`. Because of the magic of inline expansion, the compiler will
        // generate highly efficient code for all of this.
        bubble_sort( first, last,
            std::less<typename std::iterator_traits<ForwardIterator>::value_type>{ } );
    }


    // The C way of creating a generic sorting function is as follows. Here the array is
    // represented as a blob of raw memory with `array_size` elements, each `element_size`
    // bytes. Internally, the function computes the location of each element "manually" and uses
    // the provided comparison function to find their ordering. Such functions tend to be less
    // efficient than the code above because of the overhead of calling the comparison function
    // indirectly via a pointer. The C compiler can't inline expand the body of the comparison
    // function because it doesn't know that at compile-time.
    //
    void bubble_sort(
        void *first, std::size_t array_size, std::size_t element_size, bool (*compare)(void *, void *) );

}

#endif
