#
# A simple Makefile for Me!
#

# Paths for libraries and includes for linking (don't change!)
# -I/usr/include 
COPTS =  -g3 -Wall  -Werror -ansi -pedantic


# The list of code files, object files, and the compiler to use

# Define our source code (change)
CFILES = test.c

# Define the .o files to correspond with the .c files
OFILES = $(CFILES:.c=.o)

# Use the C compiler
CC = g++

# Name of the compiled output (change)
TARGET = prog


# Makefile terminal commands:  make == make default

default: clean go

.c.o: $(CFILES) 
	$(CC) -c $< $(COPTS)

go: $(OFILES) 
	$(CC) $(OFILES)  -o $(TARGET) 

clean:
	rm -f $(OFILES) $(TARGET) core

cleanall:
	rm -f $(OFILES) out.ppm *~ $(TARGET) core


