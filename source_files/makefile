IDIR = ../include/
SDIR = ../source/
TDIR = ../test/

DEPS = utils.h

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)
RM = rm -rf

TARGETS := vector slist slist_ex queue cbuffer dlist uid fixed_size_allocator variable_size_allocator

.PHONY = all clean

all: $(TARGETS)

scheduler: scheduler.c $(TDIR)scheduler_test.c task.c pqueue.c UID.c sorted_list.c dlist.c
	$(CC) $(CFLAGS) -o a.out $^

pqueue: $(IDIR)pqueue.h pqueue.c $(TDIR)pqueue_test.c $(IDIR)$(DEPS) $(IDIR)sorted_list.h sorted_list.c $(IDIR)dlist.h dlist.c
	$(CC) $(CFLAGS) -o a.out $^

sorted_list: $(IDIR)sorted_list.h sorted_list.c $(TDIR)sorted_list_test.c $(IDIR)$(DEPS) $(IDIR)dlist.h dlist.c
	$(CC) $(CFLAGS) -o a.out $^

queue: $(IDIR)queue.h queue.c $(TDIR)queue_test.c $(IDIR)$(DEPS) $(IDIR)slist.h slist.c
	$(CC) $(CFLAGS) -o $@ $^

%: $(TDIR)%_test.c %.c $(IDIR)%.h $(IDIR)$(DEPS)
	$(CC) $(CFLAGS) -o a.out $^

clean:
	$(RM) *.o $(TARGETS)
