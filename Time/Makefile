#
# Makefile for the Time demo.
#

CXX=g++
CXXFLAGS=-c -std=c++20 -Wall -DDEBUG -O0 -g
LINK=g++
LINKFLAGS=-g

# Program Sources
#################
SOURCES=Time_test.cpp Time.cpp
OBJECTS=$(SOURCES:.cpp=.o)
PROG=Time_test

# Main Target
#############
all:	$(PROG)

# Global Link
#############

$(PROG):	$(OBJECTS)
	$(LINK) $(OBJECTS) $(LINKFLAGS) -o $@

# File Dependencies
###################

Time_test.o:		Time_test.cpp Time.hpp

Time.o:				Time.cpp Time.hpp

# Additional Rules
##################
# -f  : Force. No error is produced if files don't exist.
# *.o : Native object files (if any)
# *~  : Emacs (and other editors) backup files (if any)
clean:
	rm -f *.o $(PROG)  *~
