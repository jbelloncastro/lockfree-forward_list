
#include <forward_list.hpp>

#include <omp.h>
#include <gtest/gtest.h>

TEST(Concurrency,FrontInsertion) {
	ASSERT_GT( omp_get_max_threads(), 1 );

	int elements = 10000;
	ads::forward_list<int> list;
	EXPECT_TRUE( list.empty() );

	#pragma omp parallel for
	for( int i = 0; i < elements; i++ )
		list.push_front( i );

	EXPECT_FALSE( list.empty() );

	int count = 0;
	for( int& v: list )
		count++;

	EXPECT_EQ( elements, count );
}

TEST(Concurrency,FrontDeletion) {
	ASSERT_GT( omp_get_max_threads(), 1 );
	omp_set_nested(1);

	int elements = 10000;
	ads::forward_list<int> list;
	EXPECT_TRUE( list.empty() );

	for( int i = 0; i < 10000; i++ )
		list.push_front( i );

	#pragma omp parallel for
	for( int i = 0; i < 10000; i++ ) {
		if( !list.empty() ) list.pop_front();
	}

	EXPECT_TRUE( list.empty() );
}

int main ( int argc, char* argv[] )
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
