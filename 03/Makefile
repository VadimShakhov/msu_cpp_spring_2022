CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

test_bin: test.cpp Matrix.hpp Matrix.cpp
	$(CC) $(FLAGS) test.cpp Matrix.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o
 
