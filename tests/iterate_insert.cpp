
#include <forward_list.hpp>
#include <iostream>

int main( int argc, char* argv[] )
{
	bool success = true;

	ads::forward_list<int> list;
	for( int i = 0; i < 1000; i++ ) {
		list.push_front(i);
	}

	auto it = list.cbegin();
	for( int i = 999; i >=0 && success; i-- ) {
		success &= (*it++) == i;
	}

	if( success ) {
		std::cerr << "Test passed" << std::endl;
	} else {
		std::cerr << "Test failed" << std::endl;
	}
	return success;
}

