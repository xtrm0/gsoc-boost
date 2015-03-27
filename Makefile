example: main.cpp vector.hpp
	g++ -Wall -std=c++11 main.cpp -o main

tests: tests.cpp vector.hpp
	g++ -Wall -std=c++11 tests.cpp -o tests

runtests: tests
	./tests

runtestsmemory: tests
	valgrind --leak-check=full ./tests

