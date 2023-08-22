#
# Makefile for the Animal project.
#

CXX=g++
CXXFLAGS=-std=c++11 -Wall -c -O
LINK=g++
LINKFLAGS=
SOURCES=Animal_demo.cpp \
	Animal.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=Animal_demo

all:	Animal_demo

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LINKFLAGS) -o $@

# File Dependencies
###################

Animal_demo.o:	Animal_demo.cpp Animal.hpp

Animal.o:	Animal.cpp Animal.hpp

# Additional Rules
##################
clean:
	rm -f *.bc *.o $(EXECUTABLE) *.s *.ll *~
