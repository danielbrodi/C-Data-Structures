IDIR = ../include/
SDIR = ../source/
TDIR = ../test/

DEPS = utils.h

CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g -lm -I$(IDIR)
RM = rm -rf

TARGETS := vector slist slist_ex queue cbuffer dlist uid fixed_size_allocator variable_size_allocator cmp_sort bs_tree sorts rbst

.PHONY = all clean

all: $(TARGETS)

ktour: knight_tour.c $(TDIR)knight_tour_test.c bit_array.c
	$(CC) $(CFLAGS) -o a.out $^
heapq: heap.c heap_queue.c $(TDIR)pqueue_test.c vector.c
	$(CC) $(CFLAGS) -o a.out $^
hash: hash.c $(TDIR)hash_test.c dlist.c
	$(CC) $(CFLAGS) -o a.out $^
rec: recursion.c $(TDIR)recursion_test.c int_stack.c stack.c
	$(CC) $(CFLAGS) -o a.out $^
scheduler: scheduler.c $(TDIR)scheduler_test.c task.c pqueue.c UID.c sorted_list.c dlist.c
	$(CC) $(CFLAGS) -o a.out $^

pqueue: $(IDIR)pqueue.h pqueue.c $(TDIR)pqueue_test.c $(IDIR)$(DEPS) $(IDIR)sorted_list.h sorted_list.c $(IDIR)dlist.h dlist.c
	$(CC) $(CFLAGS) -o a.out $^

sorted_list: $(IDIR)sorted_list.h sorted_list.c $(TDIR)sorted_list_test.c $(IDIR)$(DEPS) $(IDIR)dlist.h dlist.c
	$(CC) $(CFLAGS) -o a.out $^

queue: $(IDIR)queue.h queue.c $(TDIR)queue_test.c $(IDIR)$(DEPS) $(IDIR)slist.h slist.c
	$(CC) $(CFLAGS) -o $@ $^

%: $(TDIR)%_test.c %.c
	$(CC) $(CFLAGS) -o a.out $^ -lm

clean:
	$(RM) *.o $(TARGETS)
