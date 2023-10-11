
#ifndef VTSU_ROTATE_LEFT_HPP
#define VTSU_ROTATE_LEFT_HPP

#include <iterator>

namespace vtsu {

    // 1 2 3 4 5
    // 2 3 4 5 1

    // This template rotates a sequence delimited by forward iterators in the manner as show
    // above.
    template<typename ForwardIterator>
    void rotate_left(ForwardIterator first, ForwardIterator last)
    {
        // It is necessary to create a temporary variable to hold an object from the sequence. But
        // what is that object's type? The std::iterator_traits template contains nested type
        // aliases that specify the `value_type` of the given iterator. Whenever an interator type
        // is defined, the programmer should also create a specialization of iterator_traits with an
        // appropriate `value_type` alias.
        //
        // The `typename` in front of the declaration below is required so the compiler
        // understands that the name `value_type` inside the traits structure is the name of a
        // type. C++ needs to know what are type names and what aren't in order to parse your
        // program. However, because templates can be manually specialized, the compiler can't
        // tell until instantiation time if this particular specialization is from the general
        // template or a manually specialized one where `value_type` is (for some reason) the
        // name of a data member. Thus you have to explain what's going on.
        
        // typename std::iterator_traits<ForwardIterator>::value_type temp( *first );

        // In C++ 2011, or above, you may find it easier to just use 'auto' to let the compiler
        // infer the complicated type above. This saves you from writing it down or worrying about
        // it. In many programs you don't really care precisely what type is involved.
        auto temp( *first );

        while( first != last ) {
            // The implementation of this template is careful to only use operations allowed for
            // forward iterators. This requires a bit of care, but it pays off by letting the
            // template be applicable to more containers.
            ForwardIterator next = first;
            ++next;
            if( next != last ) {
                *first = *next;
            }
            else {
                *first = temp;
            }
            ++first;
        }
        // This code has a bug. Do you see it?
    }

}

#endif
