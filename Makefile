
CC=g++
CPPFLAGS=-Ilockfree/
CXXFLAGS=-std=c++11 -O0 -g -fopenmp
LDFLAGS=-lgtest

tests=\
 construction-test\
 concurrent-insert-test\
#

.PHONY: all

all: $(tests)

%: tests/%.cpp
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $? -o $@

check: $(tests)
	$(foreach test,$(tests),./$(test);)

clean:
	rm -f $(tests)
