# the compiler:
CC = gcc
# compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  #  -ansi tells the compiler to implement the ANSI language option.  
  #  -pedantic used in conjunction with -ansi,  
  #  this tells the compiler to be adhere strictly to the ANSI standard, 
  #  rejecting any code which is not compliant.

CFLAGS = -ansi -pedantic-errors -Wall -Wextra -g
IFLAG = -I/home/danielbrod/daniel-brodsky/ds/include
RM = rm -rf

OUT = vector
TEST = vector_test.c
TEST_PATH = /home/danielbrod/daniel-brodsky/ds/test
SOURCE = vector.c
SRC_PATH = /home/danielbrod/daniel-brodsky/ds/source


all: build

build: vector_test.o vector.o
	$(CC) $(CFLAGS) $(IFLAG) -o $(OUT) $(TEST_PATH)$(TEST) $(SRC_PATH)$(SOURCE)
	$(RM) *-o
	
vector_test.o: $(TEST_PATH)$(TEST) 
	$(CC) $(CFLAGS) $(IFLAG) -c $(TEST_PATH)$(TEST)
	
vector_test.o: $(SRC_PATH)$(SOURCE)
	$(CC) $(CFLAGS) $(IFLAG) -c $(SRC_PATH)$(SOURCE)
	
clean:
	$(RM) *.O $(OUT)
