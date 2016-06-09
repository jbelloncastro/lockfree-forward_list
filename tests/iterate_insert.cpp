
#include <forward_list.hpp>
#include <forward_list>

#include <gtest/gtest.h>

TEST(ConstructorTest, Default) {
	std::forward_list<int> list;
	ASSERT_EQ( list.empty(), true );
}

TEST(ConstructorTest, InitializerList) {
	std::forward_list<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int i = 1;
	for( int& v: list ) {
		ASSERT_EQ( i++, v );
	}
	//EXPECT_EQ( value, function );
}

TEST(ConstructorTest, ValueInitializer) {
	int amount = 5;
	int value = 4;
	ads::forward_list<int> list( amount, value );

        int count = 0;
	for( int& v: list ) {
		ASSERT_EQ( v, value );
		count++;
	}
	ASSERT_EQ( count, amount );
}

TEST(ConstructorTest, RangeInitializer ) {
	int array[5] = {0, 1, 2, 3, 4};
	auto begin = std::begin(array);
	auto end = std::end(array);
	ads::forward_list<int> list( ++begin, --end );

	int amount = std::distance( begin, end );
	int count = 0;
	for( int& v: list ) {
		ASSERT_EQ( v, *begin++ );
		count++;
	}
	ASSERT_EQ( count, amount );
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

