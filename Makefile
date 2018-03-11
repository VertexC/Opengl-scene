#! /usr/bin/make

# Generic Makefile that should work with any program you're going to compile.
# Any complaints should be directed at honghual@sfu.ca
#
# To compile and link your program all you have to do is run 'make' in the
#    current directory.
# To clean up object files run 'make clean_object'.
# To delete any compiled files run 'make clean'.
# Originated in 2001 by Haris Teguh
# modified May-2012 by Honghua Li

# Including of non standard library files:
#   INCLUDEDIR is where the header files can be found
#   LIBDIR is where the library object files can be found
INCLUDEDIR=/usr/include/
LIBDIR=/usr/lib
# EXTRALIBDIR=./dep/
# If you have more source files add them here 
SOURCE= scene.cpp model.cpp

# The compiler we are using 
CC= g++

# The flags that will be used to compile the object file.
# If you want to debug your program,
# you can add '-g' on the following line
CFLAGS= -std=c++0x -O3 -g -Wall -pedantic -DGL_GLEXT_PROTOTYPES

# The name of the final executable 
EXECUTABLE=myscene

# The basic library we are using add the other libraries you want to link
# to your program here 

# Linux (default)
LDFLAGS = -lGL -lglut -lGLEW -lXext -lX11 -lm

# If you have other library files in a different directory add them here 
INCLUDEFLAG= -I. -I$(INCLUDEDIR) -Idep/ -Idep/soil/include/ -Idep/include/
LIBFLAG= -L$(LIBDIR) -Ldep/soil/lib -Ldep/assimp/lib
# EXTRALIBFLAG = -L$(EXTRALIBDIR)
# Don't touch this one if you don't know what you're doing 
OBJECT= $(SOURCE:.cpp=.o)
# EXTRAOBJECT= $(SOURCE:.cpp=.o)
# Don't touch any of these either if you don't know what you're doing 
all: $(OBJECT) depend
	$(CC) $(CFLAGS) $(INCLUDEFLAG) $(LIBFLAG) $(OBJECT) -o $(EXECUTABLE) $(LDFLAGS) -lSOIL -lassimp

myscene: $(OBJECT) depend
	$(CC) $(CFLAGS) $(INCLUDEFLAG) $(LIBFLAG) $(OBJECT) -o $(EXECUTABLE)  $(LDFLAGS) -lSOIL -lassimp

depend:
	$(CC) -M $(SOURCE) > depend

$(OBJECT):
	$(CC) $(CFLAGS) $(INCLUDEFLAG) -c -o $@ $(@:.o=.cpp) 

clean_object:
	rm -f $(OBJECT)

clean:
	rm -f $(OBJECT) depend $(EXECUTABLE)

include depend