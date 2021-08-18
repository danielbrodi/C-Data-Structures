#COMPILER
CC=gcc
CFLAGS=-I./header_files/ -L. -Wl,-rpath=. -Wall
CORFLAGS=-I./header_files/ -c -ansi -pedantic-errors -Wall -Wextra -g
COFLAGS=-I./header_files/ -Wall -Werror -fpic -c
CSOFLAGS=-shared
#vpath
vpath %.h ./header_files/
vpath %.c ./test_files/
vpath %.c ./source_files/
vpath %.o ./obj/
#PATH
SOURCE=./source_files/
OUT=-o ./obj/$@
TEST=./test_files/
OBJPATH=./obj/
#LISTS
CFILESWP=$(wildcard ./source_files/*.c)
TFILESWP=$(wildcard ./test_files/*.c)
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
	
#OBJFILES
%.o: %.c %.h
	$(CC) $(COFLAGS) -o $@ $< -g

#CLEAN
cleanall:
	rm -f *.o $(OBJPATH)*.o
	rm -f $(NAMES) libds.so

clean:
	rm -f *.o $(OBJPATH)*.o
