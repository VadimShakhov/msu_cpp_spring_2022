CC=g++-11
FLAGS=-std=c++20 -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

.PHONY: test clean

all: test_bin

Serializer.o: Serializer.cpp Serializer.hpp Serializer.tpp
	$(CC) $(FLAGS) Serializer.cpp -c

Deserializer.o: Deserializer.cpp Deserializer.hpp Deserializer.tpp
	$(CC) $(FLAGS) Deserializer.cpp -c

test_bin: Serializer.o Deserializer.o test.cpp
	$(CC) $(FLAGS) Serializer.o Deserializer.o test.cpp -o test_bin $(TEST_LIBS)

test:
	./test_bin
	
clean:
	rm -f *.o test_bin
 
