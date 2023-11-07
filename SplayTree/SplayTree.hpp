/*! \file   SplayTree.hpp
 *  \brief  A class for representing SplayTrees in a manner like that of the standard library.
 *  \author Peter Chapin <peter.chapin@vermontstate.edu>
 */

#ifndef SPICA_SPLAYTREE_HPP
#define SPICA_SPLAYTREE_HPP

#include <cassert>
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
        using WeakNodePointer = std::weak_ptr<Node>;

    public:
        //! The usual type aliases.
        using size_type       = std::size_t;
        using difference_type = std::ptrdiff_t;
        using value_type      = T;
        using reference       = const T &;
        using const_reference = const T &;
        using pointer         = const T *;
        using const_pointer   = const T *;

        //! An exception class thrown if a method is not implemented.
        class NotImplemented : public std::logic_error {
        public:
            NotImplemented( const std::string &message ) :
                std::logic_error( message )
            { }
        };

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
        SplayTree( std::initializer_list<T> init_list, StrictWeakOrdering swo = StrictWeakOrdering( ) );

        //! Iterator class.
        class iterator {
        public:
            // The usual type aliases.
            using iterator_category = std::bidirectional_iterator_tag;
            using value_type        = T;
            using difference_type   = std::ptrdiff_t;
            using pointer           = const T *;
            using reference         = const T &;

            iterator( const SplayTree *t ) :
                tree( t ), current( NodePointer( ) )
                { }
            iterator( const SplayTree *t, NodePointer ptr ) :
                tree( t ), current( ptr )
                { }
            
            const T &operator*( ) const { return current->data; }
            const T *operator->( ) const { return &current->data; }

            iterator &operator++( );     // Prefix version.
            iterator operator++( int );  // Postfix version.
            iterator &operator--( );     // Prefix version.
            iterator operator--( int );  // Postfix version.

            bool operator==( const iterator &other ) const { return current == other.current; }
            bool operator!=( const iterator &other ) const { return current != other.current; }

        private:
            const SplayTree  *tree;      // This is needed so end( ) is decrementable.
            NodePointer current;
        };  // End of iterator class.

        iterator begin( ) const;
        iterator end( ) const { return iterator( this ); }

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

        //! An exception class thrown `check_structure( )` detects a problem with the tree structure.
        /*!
         * If this occurs, the code is buggy and undefined behavior is likely.
         */
        class InconsistentStructure : public std::logic_error {
        public:
            InconsistentStructure( const std::string &message ) :
                std::logic_error( message )
            { }
        };
        void check_structure( ) const;

        struct DumpItem {
            size_type depth;
            T data;

            bool operator==( const DumpItem &other ) const
            {
                return depth == other.depth && data == other.data;
            }
        };
        using DumpResult = std::vector<DumpItem>;
        DumpResult dump( ) const;

    private:
        struct Node {
            T data;
            WeakNodePointer parent;  // A weak pointer to break reference cycles.
            NodePointer left;
            NodePointer right;

            Node( const T &d,
                  WeakNodePointer p = WeakNodePointer( ),
                  NodePointer l = NodePointer( ),
                  NodePointer r = NodePointer( ) ) :
                data( d ), parent( p ), left( l ), right( r )
            { }
        };

        NodePointer root;
        StrictWeakOrdering compare;
        size_type node_count;

        // The rotations take a pointer to the node initially at the root of the subtree. They
        // rotate that node down and toward the direction indicated by the name of the function.
        //
        void rotate_left( NodePointer x );
        void rotate_right( NodePointer y );

        // Starting at node x, splay the tree until x is the root.
        void splay( NodePointer x );

        // Find the node with the minimum (maximum) value in the subtree rooted at subtree_root.
        static NodePointer minimum_node( NodePointer subtree_root );
        static NodePointer maximum_node( NodePointer subtree_root );

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
    SplayTree<T, StrictWeakOrdering>::SplayTree( std::initializer_list<T> init_list, StrictWeakOrdering swo ) :
        root( NodePointer( ) ), compare( swo ), node_count( 0 )
    {
        for( const auto &item : init_list ) {
            insert( item );
        }
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::iterator &
        SplayTree<T, StrictWeakOrdering>::iterator::operator++( )
    {
        if( current != nullptr ) {
            if( current->right != nullptr ) {
                current = minimum_node( current->right );
            }
            else {
                NodePointer backtrack = current->parent.lock( );
                while( backtrack != nullptr && current == backtrack->right ) {
                    current = backtrack;
                    backtrack = backtrack->parent.lock( );
                }
                current = backtrack;
            }
        }
        return *this;
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
        // If we are an off-the-end pointer...
        if( current == nullptr ) {
            // This is why iterators need a pointer to the tree. Otherwise they can't find the
            // tree in the case when they are pointing "off-the-end" and current is nullptr.
            if( tree->root != nullptr)
                current = maximum_node( tree->root );
        }
        // Otherwise...
        else {
            if( current->left != nullptr ) {
                current = maximum_node( current->left );
            }
            else {
                NodePointer backtrack = current->parent.lock( );
                while( backtrack != nullptr && current == backtrack->left ) {
                    current = backtrack;
                    backtrack = backtrack->parent.lock( );
                }
                current = backtrack;
            }
        }
        return *this;
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::iterator
        SplayTree<T, StrictWeakOrdering>::iterator::operator--( int )
    {
        iterator saved{ *this };
        --( *this );
        return saved;
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::iterator
        SplayTree<T, StrictWeakOrdering>::begin( ) const
    {
        if( root == nullptr ) return end( );
        return iterator( this, minimum_node( root ) );
    }

    template<typename T, typename StrictWeakOrdering>
    std::pair<typename SplayTree<T, StrictWeakOrdering>::iterator, bool>
        SplayTree<T, StrictWeakOrdering>::insert( const T &value )
    {
        NodePointer new_node = std::make_shared<Node>( value );
        if( root == nullptr ) {
            root = new_node;
            node_count++;
            return { iterator( this, root ), true };
        }

        NodePointer current = root;
        while( true ) {
            if( compare( value, current->data ) ) {
                if( current->left == nullptr ) {
                    current->left = new_node;
                    new_node->parent = current;
                    node_count++;
                    splay( new_node );
                    return { iterator( this, new_node ), true };
                }
                else {
                    current = current->left;
                }
            }
            else if( compare( current->data, value ) ) {
                if( current->right == nullptr ) {
                    current->right = new_node;
                    new_node->parent = current;
                    node_count++;
                    splay( new_node );
                    return { iterator( this, new_node ), true };
                }
                else {
                    current = current->right;
                }
            }
            else {
                // The value is already in the tree.
                return { iterator( this, current ), false };
            }
        }
        assert( false );  // Should never get here.
    }

    template<typename T, typename StrictWeakOrdering>
    template<typename InputIterator>
        void SplayTree<T, StrictWeakOrdering>::insert( InputIterator first, InputIterator last )
    {
        while( first != last ) {
            insert( *first );
            ++first;
        }
    }

    template<typename T, typename StrictWeakOrdering>
    void SplayTree<T, StrictWeakOrdering>::insert( std::initializer_list<T> init_list )
    {
        insert( init_list.begin( ), init_list.end( ) );
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::iterator
        SplayTree<T, StrictWeakOrdering>::find( const T &value )
    {
        NodePointer current = root;
        while( current != nullptr ) {
            if( compare( value, current->data ) ) {
                current = current->left;
            }
            else if( compare( current->data, value ) ) {
                current = current->right;
            }
            else {
                // We found it!
                splay( current );
                return iterator( this, current );
            }
        }
        return iterator( this );
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::size_type
        SplayTree<T, StrictWeakOrdering>::erase( const T &value )
    {
        // DO NOT IMPLEMENT!
        throw NotImplemented( "erase( )" );
        return 0;
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::iterator
        SplayTree<T, StrictWeakOrdering>::erase( iterator position )
    {
        // DO NOT IMPLEMENT!
        throw NotImplemented( "erase( )" );
        return iterator( );
    }

    // Private Methods
    // ---------------

    template<typename T, typename StrictWeakOrdering>
    void SplayTree<T, StrictWeakOrdering>::rotate_left( NodePointer x )
    {
        assert( x != nullptr );

        // Turn y's left subtree into x's right subtree
        NodePointer y = x->right;
        x->right = y->left;

        // If y's left subtree is not empty, set its parent to x.
        if( y->left != nullptr ) {
            y->left->parent = x;
        }

        // Link x's parent to y.
        y->parent = x->parent;

        // If x was the root...
        if( x->parent.lock( ) == nullptr ) {
            root = y;
        }
        // ... otherwise fix x's parent to point at y.
        else if( x == x->parent.lock( )->left ) {
            x->parent.lock( )->left = y;
        }
        else {
            x->parent.lock( )->right = y;
        }

        // Attach x as the left child of y.
        y->left = x;
        x->parent = y;
    }

    template<typename T, typename StrictWeakOrdering>
    void SplayTree<T, StrictWeakOrdering>::rotate_right( NodePointer y )
    {
        assert( y != nullptr );

        // Turn x's right subtree into y's left subtree
        NodePointer x = y->left;
        y->left = x->right;

        // If x's right subtree is not empty, set its parent to y.
        if( x->right != nullptr ) {
            x->right->parent = y;
        }

        // Link y's parent to x.
        x->parent = y->parent;

        // If y was the root...
        if( y->parent.lock( ) == nullptr ) {
            root = x;
        }
        // ... otherwise fix y's parent to point at x.
        else if( y == y->parent.lock( )->left ) {
            y->parent.lock( )->left = x;
        }
        else {
            y->parent.lock( )->right = x;
        }

        // Attach y as the right child of x.
        x->right = y;
        y->parent = x;
    }

    template<typename T, typename StrictWeakOrdering>
    void SplayTree<T, StrictWeakOrdering>::splay( NodePointer x )
    {
        assert( x != nullptr );

        while( x->parent.lock( ) != nullptr ) {
            NodePointer x_parent = x->parent.lock( );
            NodePointer x_grandparent = x_parent->parent.lock( );

            // If x's parent is the root of the tree...
            if( x_grandparent == nullptr ) {
                if( x == x_parent->left ) {
                    rotate_right( x_parent );
                }
                else {
                    rotate_left( x_parent );
                }
            }
            // If x is the left child of its parent...
            else if( x == x_parent->left ) {
                // ... and its parent is the left child of its grandparent (Zig-Zig)...
                if( x_parent == x_grandparent->left ) {
                    rotate_right( x_grandparent );
                    rotate_right( x_parent );
                }
                // ... and its parent is the right child of its grandparent (Zig-Zag)...
                else {
                    rotate_right( x_parent );
                    rotate_left( x->parent.lock( ) );  // Look up the new parent!
                }
            }
            // Otherwise x is the right child of its parent...
            else {
                // ... and if its parent is the left child of its grandparent (Zig-Zag)...
                if( x_parent == x_grandparent->left ) {
                    rotate_left( x_parent );
                    rotate_right( x->parent.lock( ) );  // Look up the new parent!
                }
                // ... and if its parent is the right child of its grandparent (Zig-Zig)...
                else {
                    rotate_left( x_grandparent );
                    rotate_left( x_parent );
                }
            }
        }
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::NodePointer
        SplayTree<T, StrictWeakOrdering>::minimum_node( NodePointer subtree_root )
    {
        assert( subtree_root != nullptr );

        NodePointer current = subtree_root;
        while( current->left != nullptr ) {
            current = current->left;
        }
        return current;
    }

    template<typename T, typename StrictWeakOrdering>
    typename SplayTree<T, StrictWeakOrdering>::NodePointer
        SplayTree<T, StrictWeakOrdering>::maximum_node( NodePointer subtree_root )
    {
        assert( subtree_root != nullptr );

        NodePointer current = subtree_root;
        while( current->right != nullptr ) {
            current = current->right;
        }
        return current;
    }

    // Testing/Debugging
    // -----------------

    template<typename T, typename StrictWeakOrdering>
    void SplayTree<T, StrictWeakOrdering>::check_structure( ) const
    {
        if( root == nullptr && node_count == 0 ) return;
        if( root == nullptr && node_count != 0 )
            throw InconsistentStructure( "Non-zero node count with a null root" );
        // The root cannot be nullptr beyond this point.

        if( root->parent.lock( ) != nullptr )
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
                if( p->left->parent.lock( ) != p ) {
                    throw InconsistentStructure( "Left child has bad parent" );
                }
                subtree_count += traverse_check( p->left );
            }
            if( p->right != nullptr ) {
                // See comment above. A mirror issue exists here.
                //
                if( !compare( p->data, p->right->data ) ) {
                    throw InconsistentStructure( "Right child out of order" );
                }
                if( p->right->parent.lock( ) != p ) {
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