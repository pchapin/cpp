
#ifndef ROTATE_HPP
#define ROTATE_HPP

#include <iterator>

// 1 2 3 4 5
// 2 3 4 5 1

// This template rotates a sequence delimited by forward iterators in the manner as show above.
template<typename ForwardIterator>
void rotate(ForwardIterator first, ForwardIterator last)
{
    // It is necessary to create a temporary variable to hold an object from the sequence. But
    // what is that object's type? The std::iterator_traits template contains nested typedef
    // names that specify the 'value_type' of the given iterator. Whenever an interator type is
    // defined, the programmer should also create a specialization of iterator_traits. This can
    // be easily done, however, by deriving the iterator types from std::iterator.
    //
    // The 'typename' in front of the declaration is required so the compiler understands that
    // the name 'value_type' inside the traits structure is the name of a type. C++ needs to
    // know what are type names and what aren't in order to parse your program. However, because
    // templates can be manually specialized, the compiler can't tell until instantiation time
    // if this particular instantiation is from the general template or a specialized one where
    // 'value_type' is the name of a data member. Thus you have to explain what's going on.

    // typename std::iterator_traits<ForwardIterator>::value_type temp( *first );

    // In C++ 2011 you may find it easier to just use 'auto' to let the compiler infer the
    // complicated type above. This saves you from writing it down or worrying about it. In many
    // programs you don't really care precisely what type is involved.
    auto temp( *first );

    while( first != last ) {
        // The implementation of this template is careful to only use operations allowed for
        // ForwardIterator. This requires a bit of care, but it pays off by letting the template
        // be applicable to more containers.
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
}

#endif
