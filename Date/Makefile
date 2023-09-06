#
# Makefile for the various Date demos.
#

CXX=g++
CXXFLAGS=-std=c++20 -Wall -DDEBUG -O0 -g
LINK=g++
LINKFLAGS=-g

# Program Sources
#################
SOURCES1=Date1_demo.cpp Date1.cpp
OBJECTS1=$(SOURCES1:.cpp=.o)
PROG1=Date1_demo

SOURCES2=Date2_demo.cpp Date2.cpp
OBJECTS2=$(SOURCES2:.cpp=.o)
PROG2=Date2_demo

SOURCES3=Date3_demo.cpp Date3.cpp
OBJECTS3=$(SOURCES3:.cpp=.o)
PROG3=Date3_demo

SOURCES_SANDBOX=sandbox.cpp
OBJECTS_SANDBOX=$(SOURCES_SANDBOX:.cpp=.o)
SANDBOX=sandbox

# Main Target
#############
all:	$(PROG1) $(PROG2) $(PROG3)

doc:
	doxygen

# Global Link
#############

# PROG1
$(PROG1):	$(OBJECTS1)
	$(LINK) $(OBJECTS1) $(LINKFLAGS) -o $@

# PROG2
$(PROG2):	$(OBJECTS2)
	$(LINK) $(OBJECTS2) $(LINKFLAGS) -o $@

# PROG3
$(PROG3):	$(OBJECTS3)
	$(LINK) $(OBJECTS3) $(LINKFLAGS) -o $@

# Sandbox
$(SANDBOX):	$(OBJECTS_SANDBOX)
	$(LINK) $(OBJECTS_SANDBOX) $(LINKFLAGS) -o $@

# File Dependencies
###################

Date1_demo.o:		Date1_demo.cpp Date1.hpp

Date2_demo.o:		Date2_demo.cpp Date2.hpp

Date3_demo.o:		Date3_demo.cpp Date3.hpp

Date1.o:			Date1.cpp Date1.hpp

Date2.o:			Date2.cpp Date2.hpp

Date3.o:			Date3.cpp Date3.hpp

sandbox.o:			sandbox.cpp Date3.hpp

# Additional Rules
##################
# -f   : Force. No error is produced if files don't exist.
# *.bc : LLVM bitcode files (if any)
# *.o  : Native object files (if any)
# *.ll : LLVM assembly language files (if any)
# *.s  : Native assembly langauge files (if any)
# *~   : Emacs (and other editors) backup files (if any)
clean:
	rm -f *.bc *.o $(PROG1) $(PROG2) $(PROG3) $(SANDBOX) *.s *.ll *~
