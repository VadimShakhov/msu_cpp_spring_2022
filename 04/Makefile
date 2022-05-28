CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

BigInt.o: BigInt.cpp BigInt.hpp
	$(CC) $(FLAGS) BigInt.cpp -c

test_bin: BigInt.o test.cpp
	$(CC) $(FLAGS) BigInt.o test.cpp -o test_bin $(TEST_LIBS)

test:
	valgrind ./test_bin

clean:
	rm -f *.o test_bin
 
