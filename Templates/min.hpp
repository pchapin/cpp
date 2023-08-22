
#ifndef MIN_HPP
#define MIN_HPP

namespace vtc {


    // A simple function that computes the minimum of two integers.
    inline int min( int x, int y )
    {
        // This uses C's (and C++'s) conditional expression form. It works similarly to if
        // expressions in functional languages.
        return (x < y) ? x : y;
    }


    // A different (overloaded) version of min that works with two doubles.
    inline double min( double x, double y )
    {
        return (x < y) ? x : y;
    }


    // Clearly duplicating min for every type of interest is a chore. C++ allows you to create a
    // "template" from which the compiler will automatically instantiate different versions of
    // the function.
    

    // The template starts with a header that declares a type parameter (named "T" in this case).
    template< typename T >
    T min( T x, T y )
    {
        return (x < y) ? x : y;
    }

    // See min_demo.cpp for how this template can be used.

}

#endif

// Comparing with Java Generics
// ============================
//
// In C++
// ------
//
// 1. Each instantiation of a template causes the compiler to generate new code (code bloat).
// 2. Each instantiation can be specialized (optimized) by the compiler independently (fast).
// 3. The validity of the operations in a template is checked at instantiation time.
//      *** Errors in the template often don't show up until an instantiation is attempted.
//      *** It's possible that one instantiation will work and others will fail.
// PROS:
//    -- The template instances are fast.
//    -- The programmer doesn't have to fuss with declaring characteristics of the types.
//
// CONS:
//    -- Can produce code bloat.
//    -- Errors message tend to be confusing.

// In Java
// -------
//
// 1. A generic is compiled ONCE AND FOR ALL.
// 2. Every usage of a generic calls the same code so that code is not necessarily optimal.
// 3. The validity of the operations in a generic is checked when the generic is compiled.
//      *** None of the usages of the generic will fail (due to, e. g., type errors).
//
// PROS:
//   -- More space efficient.
//   -- Better error messages.
//
// CONS:
//   -- Can be slower.
//   -- Programmer has to declare information about the types used in the generic.
