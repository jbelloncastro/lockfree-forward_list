
CC=g++
CPPFLAGS=-Ilockfree/
CXXFLAGS=-std=c++11 -O0 -g
LDFLAGS=-lgtest

tests=\
 iterate_insert

.PHONY: all

all: $(tests)

%: tests/%.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $? -o $@

check: $(tests)
	$(foreach test,$(tests),./$(test))

clean:
	rm -f $(tests)
