#
# Makefile for the various Date demos.
#

CXX=g++
CXXFLAGS=-std=c++20 -Wall -DDEBUG -O0 -g
LINK=g++
LINKFLAGS=-g

# Program Sources
#################
SOURCES1=BigInteger1_demo.cpp BigInteger1.cpp
OBJECTS1=$(SOURCES1:.cpp=.o)
PROG1=BigInteger1_demo

SOURCES2=BigInteger2_demo.cpp BigInteger2.cpp
OBJECTS2=$(SOURCES2:.cpp=.o)
PROG2=BigInteger2_demo

SOURCES3=BigInteger3_demo.cpp BigInteger3.cpp
OBJECTS3=$(SOURCES3:.cpp=.o)
PROG3=BigInteger3_demo

SOURCES4=BigInteger4_demo.cpp BigInteger4.cpp
OBJECTS4=$(SOURCES4:.cpp=.o)
PROG4=BigInteger4_demo

SOURCES_SANDBOX=sandbox.cpp
OBJECTS_SANDBOX=$(SOURCES_SANDBOX:.cpp=.o)
SANDBOX=sandbox

# Main Target
#############
all:	$(PROG1) $(PROG2) $(PROG3) $(PROG4)

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

# PROG4
$(PROG4):	$(OBJECTS4)
	$(LINK) $(OBJECTS4) $(LINKFLAGS) -o $@

# Sandbox
$(SANDBOX):	$(OBJECTS_SANDBOX)
	$(LINK) $(OBJECTS_SANDBOX) $(LINKFLAGS) -o $@


# File Dependencies
###################

BigInteger1_demo.o:	BigInteger1_demo.cpp BigInteger1.hpp

BigInteger2_demo.o:	BigInteger2_demo.cpp BigInteger2.hpp

BigInteger3_demo.o:	BigInteger3_demo.cpp BigInteger3.hpp

BitInteger4_demo.o:	BigInteger4_demo.cpp BigInteger4.hpp

BigInteger1.o:		BigInteger1.cpp BigInteger1.hpp

BigInteger2.o:		BigInteger2.cpp BigInteger2.hpp

BigInteger3.o:		BigInteger3.cpp BigInteger3.hpp

BigInteger4.o:		BigInteger4.cpp BigInteger4.hpp

sandbox.o:			sandbox.cpp

# Additional Rules
##################
# -f   : Force. No error is produced if files don't exist.
# *.bc : LLVM bitcode files (if any)
# *.o  : Native object files (if any)
# *.ll : LLVM assembly language files (if any)
# *.s  : Native assembly langauge files (if any)
# *~   : Emacs (and other editors) backup files (if any)
clean:
	rm -f *.bc *.o $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(SANDBOX) *.s *.ll *~
