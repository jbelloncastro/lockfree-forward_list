
#include <forward_list.hpp>

#include <gtest/gtest.h>

TEST(IteratorsTest, Values) {
	ads::forward_list<int> list{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int i = 1;
	for( int& v: list ) {
		EXPECT_EQ( i++, v );
	}
   //ASSERT_EQ( value, function );
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

