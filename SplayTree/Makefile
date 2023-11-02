#
# Makefile for the SplayTree demo.
#

CXX=g++
CXXFLAGS=-std=c++20 -Wall -DDEBUG -O0 -g
LINK=g++
LINKFLAGS=-g

# Program Sources
#################
SOURCES=SplayTree_demo.cpp
OBJECTS=$(SOURCES:.cpp=.o)
PROG=SplayTree_demo

# Main Target
#############
all:	$(PROG)

# Global Link
#############

# PROG
$(PROG):	$(OBJECTS)
	$(LINK) $(OBJECTS) $(LINKFLAGS) -o $@

# File Dependencies
###################

SplayTree_demo.o:	SplayTree_demo.cpp SplayTree.hpp

# Additional Rules
##################
# -f   : Force. No error is produced if files don't exist.
# *.bc : LLVM bitcode files (if any)
# *.o  : Native object files (if any)
# *.ll : LLVM assembly language files (if any)
# *.s  : Native assembly langauge files (if any)
# *~   : Emacs (and other editors) backup files (if any)
clean:
	rm -f *.bc *.o $(PROG) *.s *.ll *~
