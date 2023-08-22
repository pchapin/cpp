#
# A simple Makefile for a simple program.
#

# The default target (it is the default because it is first).
all:	query_tree

# How to make the executable.
query_tree:	query_tree.o
	g++ -g -o query_tree query_tree.o

# How to make the object file required by the executable.
#   -c        : Compile only, do not link.
#   -std=c++20: Use the C++ 2020 standard.
#   -Wall     : Activate "all" (easy to fix) warnings.
#   -DDEBUG   : Define a DEBUG macro (value set to 1) for conditional compliation.
#   -O0       : Disable the optimizer (makes the code easier to debug, but slower).
#   -g        : Add debugging information to the object file.
#
query_tree.o:	query_tree.cpp
	g++ -c -std=c++20 -Wall -DDEBUG -O0 -g query_tree.cpp

doc:
	doxygen

clean:
	rm -f query_tree query_tree.o
	rm -rf doc/HTML
