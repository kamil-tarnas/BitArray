#include <gtest/gtest.h>
#include "BitArray.h"

class BitArrayTest : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}
};

TEST_F(BitArrayTest, DummyTest_static)
{
	BitArray<4, 5, false> bitArray;
	(void)bitArray;

	for (int i = 0; i < 4; ++i)
	{
		bitArray.Set(i, i * 2);
	}

	for (int i = 0; i < 4; ++i)
	{
		EXPECT_EQ(i * 2, bitArray.Get(i));
	}
}

TEST_F(BitArrayTest, DummyTest_dynamic)
{
	BitArray<4, 5, true> bitArray;
	(void)bitArray;

	for (int i = 0; i < 4; ++i)
	{
		bitArray.Set(i, i * 2);
	}

	for (int i = 0; i < 4; ++i)
	{
		EXPECT_EQ(i * 2, bitArray.Get(i));
	}
}

int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
