CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: main test_bin

main: Allocator.o main.cpp
	$(CC) $(FLAGS) Allocator.o main.cpp -o main

fake.o: Allocator.cpp Allocator.hpp
	$(CC) $(FLAGS) Allocator.cpp -c

test_bin: Allocator.o test.cpp
	$(CC) $(FLAGS) Allocator.o test.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o main test_bin
 
