IDIR = ../include/
SDIR = ../source/
TDIR = ../test/

DEPS = utils.h

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -I$(IDIR)
RM = rm -rf

TARGETS := vector slist slist_ex queue cbuffer dlist uid

.PHONY = all clean

all: $(TARGETS)

scheduler: $(IDIR)scheduler.h scheduler.c $(TDIR)scheduler_test.c $(IDIR)task.h task.c $(IDIR)$(DEPS) $(IDIR)pqueue.h pqueue.c $(IDIR)UID.h UID.c $(IDIR)sorted_list.h sorted_list.c $(IDIR)dlist.h dlist.c
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
