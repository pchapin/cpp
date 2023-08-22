#
# Makefile for the Sample project.
#

CXX=g++
CXXFLAGS=-std=c++20 -Wall -c -O
LINK=g++
LINKFLAGS=
SOURCES=bubble_demo.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=bubble_demo

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LINKFLAGS) -o $@
	
all:	$(EXECUTABLE)

# File Dependencies
###################

bubble_demo.o:	bubble_demo.cpp bubble_sort.hpp

# Additional Rules
##################
clean:
	rm -f *.bc *.o $(EXECUTABLE) *.s *.ll *~
