CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

format.o: format.hpp format.tpp my_exceptions.hpp
	$(CC) $(FLAGS) format.cpp -c

test_bin: test.cpp format.hpp format.tpp my_exceptions.hpp
	$(CC) $(FLAGS) test.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin

clean:
	rm -f *.o test_bin
 
