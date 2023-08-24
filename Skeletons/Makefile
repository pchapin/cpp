#
# Makefile for the Skeletons. This file builds all skeleton programs.
#

CXX=g++
CXXFLAGS=-c -std=c++20 -Wall -DDEBUG -O0 -g
LINK=g++
LINKFLAGS=-g

# Program Sources
#################
SOURCES1=filter_by_char.cpp
OBJECTS1=$(SOURCES1:.cpp=.o)
PROG1=filter_by_char

SOURCES2=filter_by_line.cpp
OBJECTS2=$(SOURCES2:.cpp=.o)
PROG2=filter_by_line

SOURCES3=reverse_lines.cpp
OBJECTS3=$(SOURCES3:.cpp=.o)
PROG3=reverse_lines

SOURCES4=reverse_file.cpp
OBJECTS4=$(SOURCES4:.cpp=.o)
PROG4=reverse_file

SOURCES5=word_count.cpp
OBJECTS5=$(SOURCES5:.cpp=.o)
PROG5=word_count

# Main Target
#############
all:	$(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5)

# Global Link
#############

# PROG1
$(PROG1):	$(OBJECTS1)
	$(CXX) $(OBJECTS1) $(LINKFLAGS) -o $@

#PROG2
$(PROG2):	$(OBJECTS2)
	$(CXX) $(OBJECTS2) $(LINKFLAGS) -o $@

#PROG3
$(PROG3):	$(OBJECTS3)
	$(CXX) $(OBJECTS3) $(LINKFLAGS) -o $@

#PROG4
$(PROG4):	$(OBJECTS4)
	$(CXX) $(OBJECTS4) $(LINKFLAGS) -o $@

#PROG5
$(PROG5):	$(OBJECTS5)
	$(CXX) $(OBJECTS5) $(LINKFLAGS) -o $@

# File Dependencies
###################

filter_by_char.o:	filter_by_char.cpp

filter_by_line.o:	filter_by_line.cpp

reverse_lines.o:	reverse_lines.cpp

reverse_file.o:		reverse_file.cpp

word_count.o:		word_count.cpp

# Additional Rules
##################
# -f   : Force. No error is produced if files don't exist.
# *.bc : LLVM bitcode files (if any)
# *.o  : Native object files (if any)
# *.ll : LLVM assembly language files (if any)
# *.s  : Native assembly langauge files (if any)
# *~   : Emacs (and other editors) backup files (if any)
clean:
	rm -f *.bc *.o $(PROG1) $(PROG2) $(PROG3) $(PROG4) $(PROG5) *.s *.ll *~
