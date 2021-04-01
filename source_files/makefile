IDIR = ../include/
SDIR = ../source/
TDIR = ../test/

DEPS = utils.h

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)
RM = rm -rf

TARGETS := vector slist slist_ex queue cbuffer dlist

.PHONY = all clean

all: $(TARGETS)

queue: $(IDIR)queue.h queue.c $(TDIR)queue_test.c $(IDIR)$(DEPS) $(IDIR)slist.h slist.c
	$(CC) $(CFLAGS) -o $@ $^

%: $(TDIR)%_test.c %.c $(IDIR)%.h $(IDIR)$(DEPS)
	$(CC) $(CFLAGS) -o a.out $^

clean:
	$(RM) *.o $(TARGETS)
