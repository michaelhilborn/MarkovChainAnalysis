#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CXX = g++
CXXFLAGS  = -Wall -g

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: main

# To create the executable file count we need the object files
# main.o GeneralTree.o, Fraction.o, MarkovChain.o:
#
main:  main.o GeneralTree.o MarkovChain.o
	$(CXX) $(CXXFLAGS) -o main main.o GeneralTree.o Fraction.o MarkovChain.o

# To create the object file countwords.o, we need the source
# files GeneralTree.cpp GeneralTree.h:
#
GeneralTree.o:  GeneralTree.cpp GeneralTree.h 
	$(CXX) $(CXXFLAGS) -c GeneralTree.cpp

# To create the object file MarkovChain.o, we need the source files
# MarkovChain.cpp and MarkovChain.h, GeneralTree.h, Fraction.h:
#
MarkovChain.o:  MarkovChain.cpp MarkovChain.h GeneralTree.h
	$(CXX) $(CXXFLAGS) -c MarkovChain.cpp

# To create the object file Fraction.o need the source files
# Fraction.cpp and Fraction.h:
#
#Fraction.o:  Fraction.cpp Fraction.h 
#	$(CXX) $(CXXFLAGS) -c Fraction.cpp

# To create the object file main.o, we need the source files
# main.cpp Fraction.h GeneralTree.h MarkovChain.h:
#
main.o:  main.cpp GeneralTree.h MarkovChain.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) main *.o *~