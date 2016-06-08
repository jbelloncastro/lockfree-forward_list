
CC=g++
CPPFLAGS=-Ilockfree/
CXXFLAGS=-std=c++11 -O0 -g


tests=\
 iterate_insert

.PHONY: all

all: $(tests)

%: tests/%.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $? -o $@

clean:
	rm -f $(tests)
