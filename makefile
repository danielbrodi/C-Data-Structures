#COMPILER
CC=gcc
CFLAGS=-I./include/ -L/home/danel/Desktop/git/ds/ -Wl,-rpath=/home/danel/Desktop/git/ds/ -Wall
CORFLAGS=-I./include/ -c -ansi -pedantic-errors -Wall -Wextra -g
COFLAGS=-I./include/ -Wall -Werror -fpic
CSOFLAGS=-shared -o
#vpath
vpath %.h ./include/
vpath %.c ./test/
vpath %.c ./source/
vpath %.o ./obj/
#PATH
SOURCE=./source/
OUT=-o ./obj/$@
TEST=./test/
OBJPATH=./obj/
#LISTS
CFILESWP=$(wildcard ./source/*.c)
TFILESWP=$(wildcard ./test/*.c)
CFILES=$(notdir $(CFILESWP))
TFILES=$(notdir $(TFILESWP))
TOFILES=$(TFILES:.c=.o)
OFILES=$(CFILES:.c=.o)
OFILESWP=$(addprefix ./obj/,$(OFILES))
NAMES=$(TOFILES:_test.o=)
HFILES=$(CFILES:.c=.h)
	


.PHONY: clean, debug, release, all

all: libds.so $(NAMES)


$(NAMES): $(TOFILES)
	$(CC) $(CFLAGS) -o $@ $(OBJPATH)$@_test.o -lds
	

#SHARED LIBRARY
libds.so: $(OFILES) $(HFILES)
	$(CC) $(CSOFLAGS) libds.so $(OFILESWP)
	

#OBJFILES
%.o: %.c
	$(CC) $(COFLAGS) -o $(OBJPATH)$@ -c $<


#CLEAN

clean:
	rm -f $(OBJPATH)*.o	
	rm -f $(NAMES) libds.so
