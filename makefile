#COMPILER
CC=gcc
CFLAGS=-I./include/ -L. -Wl,-rpath=. -Wall
CORFLAGS=-I./include/ -c -ansi -pedantic-errors -Wall -Wextra -g
COFLAGS=-I./include/ -Wall -Werror -fpic -c
CSOFLAGS=-shared
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
	
	
.PHONY: clean debug release all

debug: CSOFLAGS+=-g
debug: libds.so

release: CSOFLAGS+=-O2
release: libds.so

test: $(NAMES)
		
all: libds.so $(NAMES)

%: %_test.c libds.so
	$(CC) $(CFLAGS) -o $@ $< -lds -g
	
#SHARED LIBRARY
libds.so: $(OFILES)
	$(CC) $(CSOFLAGS) -o libds.so $(OFILES)
	mv *.o $(OBJPATH)
	
#OBJFILES
%.o: %.c %.h
	$(CC) $(COFLAGS) -o $@ $< -g

#CLEAN
clean:
	rm -f *.o $(OBJPATH)*.o
	rm -f $(NAMES) libds.so
