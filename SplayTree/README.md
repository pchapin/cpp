
SplayTree
=========

This folder contains an implementation of Splay Trees in C++. This version experiments with
using shared pointers in the nodes. Because Splay Trees have parent pointers, a node is
necessarily pointed at by more than one node. This is why shared pointers and not unique
pointers are needed. Actually, to avoid reference cycles, the parent pointers are weak pointers,
but those can only be generated from an existing shared pointer.

The beauty of using shared pointers is that the compiler-generated destructor correctly disposes
of the entire tree. Destroying the shared pointers in a node triggers the deletion (and
destruction) of the nodes pointed at by those pointers, etc. recursively.

Unfortunately, this creates a problem for Splay Trees. Unlike certain other kinds of trees (such
as Red-Black trees), Splay Trees are sometimes highly unbalanced. If a splay tree is destroyed
while in a highly unbalanced state, the compiler-generated destructor will cause stack overflow
as it recurses down the tree. The test program in this folder happens to create that
circumstances making the issue evident.

To avoid this problem, Splay Trees need to have iterative (not recursive) destructors. In fact,
all the methods of a Splay Tree should be iterative. As a consequence, the neat usage of shared
pointers is not really appropriate in this case.

Note that this is really a quirk of Splay Tree. Using shared pointers in this way for a tree
structure that stays relatively balanced, such as Red-Black Tree (or others), should work fine.
In that case, the depth of the recursion encountered during tree destruction should remain
moderate even for the case of a very large tree.
