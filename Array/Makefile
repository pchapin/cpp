#
# Makefile for the Sample project.
#

CXX=g++
CXXFLAGS=-std=c++11 -Wall -c -O
LINK=g++
LINKFLAGS=
SOURCES=Array_demo.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Array_demo

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LINKFLAGS) -o $@
	
all:	$(EXECUTABLE)

# File Dependencies
###################

Array_demo.o:	Array_demo.cpp ArrayStatic.hpp ArrayDynamic.hpp

# Additional Rules
##################
clean:
	rm -f *.bc *.o $(EXECUTABLE) *.s *.ll *~
