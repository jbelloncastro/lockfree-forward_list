
#include <forward_list.hpp>

#include <omp.h>
#include <gtest/gtest.h>

TEST(Concurrency,FrontInsertion) {
	ASSERT_GT( omp_get_max_threads(), 1 );

	int elements = 10000;
	ads::forward_list<int> list;

	#pragma omp parallel for
	for( int i = 0; i < 10000; i++ )
		list.push_front( i );

	EXPECT_FALSE( list.empty() );

	int count = 0;
	for( int& v: list )
		count++;

	EXPECT_EQ( elements, count );
}

int main ( int argc, char* argv[] )
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
