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
vpath %.d ./obj/
#COMPILER
CC=gcc
CFLAGS=-ansi -pedantic-errors -Wall -Wextra -fpic -g -I$(HDRDIR) # C flags
LDFLAGS=-L./ -Wl,-rpath=./ # linking flags
TARGET_LIB = libds.so  # target lib
LDLIBS=-lds
#FILES
TESTS=$(wildcard ./test/*.c)
CFILESWP=$(patsubst %_test.c,%.c,$(TESTS))
SRCS=$(notdir $(CFILESWP))
TARGETS=$(patsubst %.c,%,$(SRCS))
SRCOBJS=$(SRCS:.c=.o)
TSTOBJS=$(TESTS:.c=.o)
HFILES=$(SRCS:.c=.h)

.PHONY: all clean

# build shared objects
all: ${TARGET_LIB} 
# build executable (ELF) files with dubged shared object 
test: $(TARGETS)

#CREATE EXECUTABLES
$(TARGETS): $(TSTOBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(TSTDIR)$@_test.o -o $@ $(LDLIBS)
	mv $(TSTDIR)$@_test.o $(OBJDIR)
	
#CREATE A SHARED LIBRARY
$(TARGET_LIB): $(SRCOBJS) $(HFILES)
	$(CC) -shared -o $@ $^
	mv *.o $(OBJDIR)
	
$(SRCS:.c=.d):%.d:%.c %.h
	$(CC) $(CFLAGS) -MM $< >$@
	mv *.d $(OBJDIR)
	
$(TESTS:.c=.d):%.d:%.c $(TARGETS).h
	$(CC) $(CFLAGS) -MM $< >$@
	
#%.d:%.c
#	$(CC) $(CFLAGS) -MM $< >$@
	
-include $(SRCS:.c=.d)

#CLEAN
clean:
	rm -f $(OBJDIR)*.o $(OBJDIR)*.d
	rm -f $(TARGETS) libds.so
