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
#include <sstream>
#include <vector>

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

        // Testing/Debugging
        // -----------------
        class InconsistentStructure : public std::logic_error {
        public:
            InconsistentStructure( const std::string &message ) :
                std::logic_error( "Inconsistent SplayTree structure: " + message )
                { }
        };
        void check_structure( ) const;

        struct DumpItem {
            size_type depth;
            T data;
        };
        using DumpResult = std::vector<DumpItem>;
        DumpResult dump( ) const;

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

        // Testing/Debugging
        // -----------------
        size_type traverse_check( NodePointer p ) const;
        std::vector<DumpItem> traverse_dump( NodePointer p, size_type depth ) const;
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

    // Testing/Debugging
    // -----------------

    template<typename T, typename StrictWeakOrdering>
    bool operator==( const typename SplayTree<T, StrictWeakOrdering>::DumpItem &lhs,
                     const typename SplayTree<T, StrictWeakOrdering>::DumpItem &rhs )
    {
        return lhs.depth == rhs.depth && lhs.data == rhs.data;
    }

    template<typename T, typename StrictWeakOrdering>
    void SplayTree<T, StrictWeakOrdering>::check_structure( ) const
    {
        if( root == nullptr && node_count == 0 ) return;
        if( root == nullptr && node_count != 0 )
            throw InconsistentStructure( "Non-zero node count with a null root" );
        // The root cannot be null beyond this point.

        if( root->parent != nullptr )
            throw InconsistentStructure( "Root has a non-null parent" );

        // Explore the tree structure and count the number of nodes.
        size_type actual_count = traverse_check( root );
        if( node_count != actual_count ) {
            std::ostringstream formatter;
            formatter << "node_count (" << node_count << ") != actual_count (" << actual_count << ")";
            throw InconsistentStructure( formatter.str( ) );
        }
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::size_type
        SplayTree<T, StrictWeakOrdering>::traverse_check( NodePointer p ) const
    {
        size_type subtree_count = 0;
        if( p != nullptr ) {
            subtree_count++;

            if( p->left != nullptr ) {
                // Note that this check is incomplete. *Everything* in the left subtree should
                // come before p->data. This only verifies that the root of the left subtree
                // satisfies the invariant. Conceivably, nodes to the right of the left child
                // should actually be to p's right. That won't be caught here.
                //
                if( !compare( p->left->data, p->data ) ) {
                    throw InconsistentStructure( "Left child out of order" );
                }
                if( p->left->parent != p ) {
                    throw InconsistentStructure( "Left child has bad parent" );
                }
                subtree_count += traverse_check( p->left );
            }
            if( p->right != nullptr ) {
                // See comment above. A mirror issue exists here.
                //
                if( !compare( p->data, p->left->data ) ) {
                    throw InconsistentStructure( "Right child out of order" );
                }
                if( p->right->parent != p ) {
                    throw InconsistentStructure( "Right child has bad parent" );
                }
                subtree_count += traverse_check( p->right );
            }
        }
        return subtree_count;
    }

    template<typename T, typename StrictWeakOrdering>
    std::vector<typename SplayTree<T, StrictWeakOrdering>::DumpItem>
        SplayTree<T, StrictWeakOrdering>::dump( ) const
    {
        return traverse_dump( root, 0 );
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::DumpResult
        SplayTree<T, StrictWeakOrdering>::traverse_dump( NodePointer p, size_type depth ) const
    {
        DumpResult result;
        if( p != nullptr ) {
            auto left_result  = traverse_dump( p->left,  depth + 1 );
            result.insert( result.end( ), left_result.begin( ), left_result.end( ) );
            result.push_back( { depth, p->data } );
            auto right_result = traverse_dump( p->right, depth + 1 );
            result.insert( result.end( ), right_result.begin( ), right_result.end( ) );
        }
        return result;
    }

}

#endif