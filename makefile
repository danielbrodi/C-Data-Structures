#PATHS
SRCDIR=./source/
TSTDIR=./test/
OBJDIR=./obj/
HDRDIR=./include/
#vpaths
vpath %.h ./include/
vpath %.c ./test/
vpath %.c ./source/
vpath %.o ./obj/
#COMPILER
CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -fpic -g -I$(HDRDIR) # C flags
LDFLAGS=-L./ -Wl,-rpath=./ # linking flags
TARGET_LIB = libds.so  # target lib
LDLIBS=-lds
#FILES
TESTS=dlist_test.c
CFILESWP=$(patsubst %_test.c,%.c,$(TESTS))
SRCS=$(notdir $(CFILESWP))
TARGETS=$(patsubst %.c,%,$(SRCS))
SRCOBJS=$(SRCS:.c=.o)
TSTOBJS=$(TESTS:.c=.o)



.PHONY: all clean

all: ${TARGET_LIB} $(TARGETS)

#CREATE EXECUTABLES
$(TARGETS): dlist_test.o
	$(CC) $(CFLAGS) $(LDFLAGS) dlist_test.o -o $@ $(LDLIBS)
	
#CREATE A SHARED LIBRARY
$(TARGET_LIB): $(SRCOBJS)
	$(CC) -shared -o $@ $^

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@
	
$(TESTS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@
	
include $(SRCS:.c=.d)

#CLEAN
clean:
	rm -f ${TARGET_LIB} ${SRCOBJS} ${TSTOBJS} $(SRCS:.c=.d) $(TESTS:.c=.d)
