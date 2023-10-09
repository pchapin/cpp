
#ifndef VTSU_MIN_HPP
#define VTSU_MIN_HPP

#include <string>

namespace vtsu {


    // This `#ifdef NEVER` block isn't compiled (because NEVER isn't defined). Thus only the
    // template, below, is actually part of this file.
    #ifdef NEVER
    
    // A simple function that computes the minimum of two integers.
    int min( int x, int y )
    {
        // This uses C's (and C++'s) conditional expression form. It works similarly to if
        // expressions in functional languages.
        return (x < y) ? x : y;
    }


    // A different (overloaded) version of `min` that works with two doubles.
    double min( double x, double y )
    {
        return (x < y) ? x : y;
    }

    
    // A different (overloaded) version of `min` that works with two strings.
    // Does this even make sense?
    std::string min( std::string x, std::string y )
    {
        return (x < y) ? x : y;
    }
    
    #endif


    // Clearly, duplicating `min` for every type of interest is a chore. C++ allows you to
    // create a template from which the compiler will automatically "instantiate" (or
    // "specialize") different versions of the function.
    

    // The template starts with a header that declares a template type parameter (named `T` in
    // this case). The name of the type parameter is arbitrary, but `T` is commonly used. In the
    // scope of the template, `T` is some, unknown type and can be used wherever it makes sense
    // to use a type name (such as in declarations).
    template<typename T>
    T min( T x, T y )
    {
        return (x < y) ? x : y;
    }

    // See min_demo.cpp for how this template can be used. Then come back here.

    // The template above doesn't really do what one might want when `min` is called with
    // arguments of two different types. A more elegant solution is to allow the arguments to
    // have different types by using multiple type parameters. Then let the compiler deduce the
    // return type during the specialization process.
    //
    template<typename T, typename U>
    auto min2( T x, U y )
    {
        return (x < y) ? x : y;
    }


    // An even more elegant approach is to use C++ 2020 auto parameters. They provide an
    // abbreviated template definition syntax. The example below is essentially the same as the
    // two-parameter template above.
    //
    auto min3( auto x, auto y )
    {
        return (x < y) ? x : y;
    }
    
}

#endif

// Comparing with Java Generics
// ============================
//
// In C++
// ------
//
// 1. Each specialization of a template causes the compiler to generate new code (code bloat).
// 2. Each specialization can be optimized by the compiler independently (fast).
// 3. The validity of the operations in a template is checked at instantiation time.
//      *** Errors in the template typically don't show up until an instantiation is attempted.
//      *** It's possible that one instantiation will work and others will fail.
// PROS:
//    -- The template instances are fast.
//    -- The programmer doesn't have to fuss with declaring characteristics of the types.
//    -- ... but in C++ 2020, you can declare those characteristics for better error handling.
//
// CONS:
//    -- Can produce code bloat.
//    -- Errors message tend to be confusing (except in C++ 2020, see above).

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
