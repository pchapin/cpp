#
# Makefile for the Time demos.
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

SOURCES_SANDBOX=sandbox.cpp
OBJECTS_SANDBOX=$(SOURCES_SANDBOX:.cpp=.o)
SANDBOX=sandbox

# Main Target
#############
all:	$(PROG)

# Global Link
#############

$(PROG):	$(OBJECTS)
	$(CXX) $(OBJECTS) $(LINKFLAGS) -o $@

# Sandbox
$(SANDBOX):	$(OBJECTS_SANDBOX)
	$(CXX)	$(OBJECTS_SANDBOX) $(LINKFLAGS) -o $@

# File Dependencies
###################

Time_test.o:		Time_test.cpp Time.hpp

Time.o:				Time.cpp Time.hpp

sandbox.o:			sandbox.cpp Time.hpp

# Additional Rules
##################
# -f   : Force. No error is produced if files don't exist.
# *.bc : LLVM bitcode files (if any)
# *.o  : Native object files (if any)
# *.ll : LLVM assembly language files (if any)
# *.s  : Native assembly langauge files (if any)
# *~   : Emacs (and other editors) backup files (if any)
clean:
	rm -f *.bc *.o $(PROG) $(SANDBOX) *.s *.ll *~
