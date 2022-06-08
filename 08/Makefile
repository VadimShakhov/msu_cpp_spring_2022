CC=g++-11
FLAGS=-std=c++20 -pthread -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

test_bin: test.cpp ThreadPool.hpp ThreadPool.tpp
	$(CC) $(FLAGS) test.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o test_bin
 
