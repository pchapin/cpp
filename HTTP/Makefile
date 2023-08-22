#
# Makefile for the Sample project.
#

CXX=g++
CXXFLAGS=-std=c++11 -Wall -c -O
LINK=g++
LINKFLAGS=
SOURCES=main.cpp HTTP.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=sample

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

$(EXECUTABLE):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LINKFLAGS) -o $@

# File Dependencies
###################

main.o:	main.cpp HTTP.hpp

HTTP.o:	HTTP.cpp HTTP.hpp

# Additional Rules
##################
clean:
	rm -f *.bc *.o $(EXECUTABLE) *.s *.ll *~
