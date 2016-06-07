
CC=g++
CPPFLAGS=-Ilockfree/
CXXFLAGS=-std=c++11 -O3 -fopenmp

forward_list: test/forward_list.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $? -o $@

clean:
	rm -f forward_list
