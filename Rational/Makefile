#
# Makefile for the Rational demo.
#

CXX=g++
CXXFLAGS=-std=c++20 -Wall -DDEBUG -O0 -g
LINK=g++
LINKFLAGS=-g

# Program Sources
#################
SOURCES1=Rational_demo.cpp
OBJECTS1=$(SOURCES1:.cpp=.o)
PROG1=Rational_demo

SOURCES2=BigRational_demo.cpp
OBJECTS2=$(SOURCES2:.cpp=.o)
PROG2=BigRational_demo

# Main Target
#############
all:	Rational_demo BigRational_demo

# Global Link
#############

# PROG1
$(PROG1):	$(OBJECTS1)
	$(CXX) $(OBJECTS1) $(LINKFLAGS) -o $@

# PROG2
$(PROG2):	$(OBJECTS2)
	$(CXX) $(OBJECTS2) $(LINKFLAGS) -o $@

# File Dependencies
###################
Rational_demo.o:	Rational_demo.cpp Rational.hpp

BigRational_demo.o:	BigRational_demo.cpp Rational.hpp ../BigInteger/BigInteger1.hpp

# Additional Rules
##################
clean:
	rm -f *.bc *.o $(PROG1) *.s *.ll *~