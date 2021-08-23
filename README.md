# Data Structures in C

This project contains implementations for many different types of data
structures commonly taught in computer science, and many of which are
commonly used in real-world production environments. 

These basic data structures represent small building blocks upon which large data-processing
applications can be built and run efficiently.

This project was created and written all by me.

### This project contains implementations of:

* [Bit Array](./source_files/bit_array.c)
* [Binary Search Tree (Iterative)](./source_files/bs_tree.c)
* [Binary Search Tree (Recursive)](./source_files/rbst.c)
* [Circular Buffer](./source_files/cbuffer.c)
* [Dynamic Host Configuration Protocol (DHCP)](./source_files/dhcp.c)
* [Doubly Linked List](./source_files/dlist.c)
* [Hash Map](./source_files/hash.c)
* [Heap Data Structure](./source_files/heap.c)
* [Heap Queue](./source_files/heap_queue.c)
* [Priority Queue](./source_files/pqueue.c)
* [Queue](./source_files/queue.c)
* [Singly Linked List](./source_files/slist.c)
* [Sorted Linked List](./source_files/sorted_list.c)
* [Stack](./source_files/stack.c)
* [Vector](./source_files/vector.c)

# Notes

1. The code for these data structures was written as `original ANSI C standard (C89)` and
thus there is no use of any "advanced" options which appeared to be later on 
more advanced standards.
Source code of all implementations are located in the [source files directory](./source_files)

2. There are test files that have been written in order to verify the validity of the codes.
All the codes were tested in a production environment,and their tests are available in the [tests files directory](./test_files).

3. Some algorithms have comments with a brief description, but some
don't. I plan to try to add more documentation to help visitors decide
which data structure and algorithm is most appropriate for their application.

4. The APIs of all the data structures are loctaed in the [header files directory](./header_files).

5. Each data structure has its own **source file, header file and a test file**, and all of them are called by the same name - the name of the data
structure: `NAME.c, NAME.h, NAME_test.c` *(e.g: stack.c, stack.h, stack_test.c)*.

6. For some reason the comments are not alligned and start or end at the same points.
It happens only when you read the file using *GitHub*, and not on every other installed IDE on your machine.

# Compiling and Running

A [Makefile](./makefile) is available and can fully compile every data structure's code.
Usage of the makefile:

`make test`
in order to compile and get an executable for each data structure,
in addition to a shared object which contains all the implementations.

`make release`
to compile and get only the shared object.

`make clean`
to remove all the `.o` and executable files and keep the shared object

`make cleanall`
to remove all files which were created by the make file (executables, object files and shared object)

# Example

#### [Hash map implementation](./source_files/hash.c), which takes all the words which exist in the [Unix dictionary](https://en.wikipedia.org/wiki/Words_(Unix)),
#### inserts them into a hash map and then runs a [spell checking program](./test_files/hash_test.c) which pulls the words using the created hash map.

![image](https://user-images.githubusercontent.com/72980285/129969894-f83748bf-d833-4eb1-b971-4061d3da0027.png)

