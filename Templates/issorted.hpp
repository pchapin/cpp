
#ifndef VTSU_ISSORTED_HPP
#define VTSU_ISSORTED_HPP

namespace vtsu {

    template<typename ForwardIterator>
    bool is_sorted( ForwardIterator first, ForwardIterator last )
    {
        while( first != last )
        {
            ForwardIterator next = first;
            ++next;
            if( next != last && *next < *first )
                return false;
            first = next;
        }
    }


    template<typename ForwardIterator, typename Compare>
    bool is_sorted( ForwardIterator first, ForwardIterator last, Compare comp )
    {
        while( first != last )
        {
            ForwardIterator next = first;
            ++next;
            if( next != last && comp( *next, *first ) )
                return false;
            first = next;
        }
    }

}

#endif
