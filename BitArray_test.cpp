#include <gtest/gtest.h>
#include "BitArray.h"

class BitArrayTest : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(BitArrayTest, DummyTest)
{
	BitArray<4, 5, false> bitArray;
	(void)bitArray;
	int cos = bitArray.Get(2);
	ASSERT_EQ(5, cos);
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
