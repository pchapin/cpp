/*! \file   SplayTree.hpp
 *  \brief  A class for representing SplayTrees in a manner like that of the standard library.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#ifndef SPICA_SPLAYTREE_HPP
#define SPICA_SPLAYTREE_HPP

#include <cstddef>
#include <functional>
#include <initializer_list>
#include <memory>

namespace spica {

    template<typename T, typename StrictWeakOrdering = std::less<T>>
    class SplayTree {
    private:
        struct Node;
        using NodePointer = std::shared_ptr<Node>;

    public:
        //! An unsigned type used for measuring the size of the tree.
        using size_type = std::size_t;

        //! Default constructor.
        SplayTree( StrictWeakOrdering swo = StrictWeakOrdering( ) ) :
            root( NodePointer( ) ), compare( swo ), node_count( 0 )
        { }

        //! Destructor (generated destructor is fine)
        // ~SplayTree( );

        //! Copy constructor (deleted for now).
        SplayTree( const SplayTree &other ) = delete;

        //! Copy assignment operator (deleted for now).
        SplayTree &operator=( const SplayTree &other ) = delete;

        //! Move constructor.
        SplayTree( SplayTree &&other );

        //! Move assignment operator.
        SplayTree &operator=( SplayTree &&other );

        //! Initializer list constructor.
        SplayTree( std::initializer_list<T> init_list );

        //! Iterator class.
        class iterator {
        public:
            iterator( ) : current( NodePointer( ) ) { }
            iterator( NodePointer ptr ) : current( ptr ) { }
            
            const T &operator*( ) const { return current->data; }
            const T *operator->( ) const { return &current->data; }

            iterator &operator++( );     // Prefix version.
            iterator operator++( int );  // Postfix version.
            iterator &operator--( );     // Prefix version.
            iterator operator--( int );  // Postfix version.

            bool operator==( const iterator &other ) const { return current == other.current; }
            bool operator!=( const iterator &other ) const { return current != other.current; }

        private:
            NodePointer current;
        };  // End of iterator class.

        //! Insert
        std::pair<iterator, bool> insert( const T &value );
        template<typename InputIterator>
            void insert( InputIterator first, InputIterator last );
        void insert( std::initializer_list<T> init_list );

        //! Find
        iterator find( const T &value );

        //! Erase
        size_type erase( const T &value );
        iterator erase( iterator position );

    private:
        struct Node {
            T data;
            NodePointer parent;
            NodePointer left;
            NodePointer right;

            Node( const T &d, NodePointer p = NodePointer( ), NodePointer l = NodePointer( ),
                  NodePointer r = NodePointer( ) ) :
                data( d ), parent( p ), left( l ), right( r )
            { }
        };

        NodePointer root;
        StrictWeakOrdering compare;
        size_type node_count;
    };

    // Implementation
    // ==============

    template<typename T, typename StrictWeakOrdering>
    SplayTree<T, StrictWeakOrdering>::SplayTree( SplayTree &&other )
    {
        root       = std::move( other.root );
        compare    = other.compare;
        node_count = other.node_count;
        other.node_count = 0;
    }

    template<typename T, typename StrictWeakOrdering>
    SplayTree<T, StrictWeakOrdering> &SplayTree<T, StrictWeakOrdering>::operator=( SplayTree &&other )
    {
        if( this != &other ) {
            root       = std::move( other.root );
            compare    = other.compare;
            node_count = other.node_count;
            other.node_count = 0;
        }
        return *this;
    }

    template<typename T, typename StrictWeakOrdering>
    SplayTree<T, StrictWeakOrdering>::SplayTree( std::initializer_list<T> init_list )
    {
        for( const auto &item : init_list ) {
            insert( item );
        }
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::iterator &
        SplayTree<T, StrictWeakOrdering>::iterator::operator++( )
    {
        // Finish me!
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::iterator
        SplayTree<T, StrictWeakOrdering>::iterator::operator++( int )
    {
        iterator saved{ *this };
        ++( *this );
        return saved;
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::iterator &
        SplayTree<T, StrictWeakOrdering>::iterator::operator--( )
    {
        // Finish me!
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::iterator
        SplayTree<T, StrictWeakOrdering>::iterator::operator--( int )
    {
        iterator saved{ *this };
        --( *this );
        return saved;
    }

}

#endif