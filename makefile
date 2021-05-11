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
LDFLAGS=-shared # linking flags
TARGET_LIB = libds.so  # target lib
#FILES
TESTS=$(wildcard ./test/*.c)
CFILESWP=$(patsubst %_test.c,%.c,$(TESTS))
SRCS=$(notdir $(CFILESWP))
TARGETS=$(patsubst %.c,%,$(SRCS))
OBJS=$(SRCS:.c=.o)


.PHONY: all
all: ${TARGET_LIB} $(TARGETS)

#CREATE EXECUTABLES
$(TARGETS): $(TESTS:.c=.o)
	$(CC) $(CFLAGS) -L. -lds $(TSTDIR)$@_test.o -o $@

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@
	
#CREATE A SHARED LIBRARY
$(TARGET_LIB): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
	
include $(SRCS:.c=.d)

#CLEAN
clean:
	rm -f ${TARGET_LIB} ${OBJS} $(SRCS:.c=.d)
