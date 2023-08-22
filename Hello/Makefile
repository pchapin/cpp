#
# A simple Makefile for a simple program.
#

# The default target (it is the default because it is first).
all:	hello

# How to make the executable.
hello:	hello.o
	g++ -g -o hello hello.o

# How to make the object file required by the executable.
#   -c        : Compile only, do not link.
#   -std=c++20: Use the C++ 2020 standard.
#   -Wall     : Activate "all" (easy to fix) warnings.
#   -DDEBUG   : Define a DEBUG macro (value set to 1) for conditional compliation.
#   -O0       : Disable the optimizer (makes the code easier to debug, but slower).
#   -g        : Add debugging information to the object file.
#
hello.o:	hello.cpp
	g++ -c -std=c++20 -Wall -DDEBUG -O0 -g hello.cpp

doc:
	doxygen

clean:
	rm -f hello hello.o
	rm -rf doc/HTML
