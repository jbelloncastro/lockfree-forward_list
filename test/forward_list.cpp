
#include <forward_list.hpp>

#include <omp.h>

int main( int argc, char* argv[] )
{
	ads::forward_list<int> list;

	int total_values;
	if( argc < 2 )
		total_values = 100*omp_get_num_threads();
	else
		total_values = atoi( argv[1] ) * omp_get_num_threads();

   for( int i = 0; i = total_values; i++ )
		list.push_front(i);

	for( int val& : list ) {
		std::cout << val << ", ";
	}
	std::cout << std::endl;

	return 0;
}
