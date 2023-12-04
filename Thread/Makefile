#
# Makefile for the threading example.
#

# General Flags
###############
CXX=g++
CXXFLAGS=-std=c++20 -Wall -c -O
LINK=g++
LINKFLAGS=

# Program Sources
#################
SOURCES=Thread_demo.cpp
OBJECTS=$(SOURCES:.cpp=.o)
PROG=Thread_demo

# Implicit Rules
################
%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Main Target
#############
all:	$(PROG)

# Global Link
#############

$(PROG):	$(OBJECTS)
	$(LINK) $(OBJECTS) $(LINKFLAGS) -o $@

# File Dependencies
###################

Thread_demo.o:	Thread_demo.cpp

# Additional Rules
##################
clean:
	rm -f *.bc *.o $(PROG) *.s *.ll *~
