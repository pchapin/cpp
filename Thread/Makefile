#
# Makefile for the threading example.
#

# General Flags
###############
CXX=g++
CXXFLAGS=-std=c++14 -Wall -pthread -c -O
LINK=g++ -pthread
LINKFLAGS=

# Program Sources
#################
SOURCES=Thread.cpp
OBJECTS=$(SOURCES:.cpp=.o)
PROG=Thread

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

main.o:	main.cpp

# Additional Rules
##################
clean:
	rm -f *.bc *.o $(PROG) *.s *.ll *~
