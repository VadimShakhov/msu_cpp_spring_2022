CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

Vector.o: Vector.hpp Vector.tpp Vector.cpp Iterator.hpp Allocator.hpp
	$(CC) $(FLAGS) Vector.cpp -c

Vector: Vector.o
	$(CC) $(FLAGS) Vector.o -o Vector

test_bin: test.cpp Vector.hpp Vector.tpp Vector.cpp Iterator.hpp Allocator.hpp
	$(CC) $(FLAGS) test.cpp -o test_bin $(TEST_LIBS)

test:
	valgrind ./test_bin

clean:
	rm -f *.o test_bin
 
