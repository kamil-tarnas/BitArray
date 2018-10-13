#include <gtest/gtest.h>
#include "BitArray_utils.h"
#include "BitArray_static.h"


class BitArray_static_test : public testing::Test
{
	virtual void SetUp() {}
	virtual void TearDown() {}
};


TEST_F(BitArray_static_test, Setting_and_getting_random_values)
{
	BitArray<4, 5> bitArray;

	for (int i = 0; i < 4; ++i)
	{
		bitArray.Set(i, i * 2);
	}

	for (int i = 0; i < 4; ++i)
	{
		EXPECT_EQ(i * 2, bitArray.Get(i));
	}
}


TEST_F(BitArray_static_test, Setting_and_getting_one_bit_per_entry)
{
	const unsigned numberOfArrayElements = 100;

	// Test filling with entries that contain all of the bits set
	{
		// One bit per element
		BitArray<100, 1> bitArray;

		for (unsigned i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 1);
		}

		for (unsigned i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(1, bitArray.Get(i));
		}
	}

	// Test filling the array with entries that are zero and one in value
	{
		// One bit per element
		BitArray<100, 1> bitArray;

		for (unsigned i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, i % 2);
		}

		for (unsigned i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(i % 2, bitArray.Get(i));
		}
	}
}


TEST_F(BitArray_static_test, Setting_and_getting_odd_sizeOfEntry_all_bits_set)
{
	constexpr unsigned numberOfArrayElements = 100;

	/*
	 * First, test all of the possible number of bits cases with one, the same literal insertion
	 * which is the maximal value that entry can hold
	 */

	// One bit per element
	{

		BitArray<numberOfArrayElements, 1> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 1);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(1, bitArray.Get(i));
		}
	}

	// Three bits per element
	{
		BitArray<numberOfArrayElements, 3> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 7);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(7, bitArray.Get(i));
		}
	}

	// Five bits per element
	{
		BitArray<numberOfArrayElements, 5> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 31);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(31, bitArray.Get(i));
		}
	}

	// Seven bits per element
	{
		BitArray<numberOfArrayElements, 7> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 127);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(127, bitArray.Get(i));
		}
	}

	// Nine bits per element
	{
		BitArray<numberOfArrayElements, 9> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 511);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(511, bitArray.Get(i));
		}
	}

	// Eleven bits per element
	{
		BitArray<numberOfArrayElements, 11> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 2047);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(2047, bitArray.Get(i));
		}
	}

	// Thirteen bits per element
	{
		BitArray<numberOfArrayElements, 13> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 8191);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(8191, bitArray.Get(i));
		}
	}

	// Fiveteen bits per element
	{
		BitArray<numberOfArrayElements, 15> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 32767);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(32767, bitArray.Get(i));
		}
	}

	// Seventeen bits per element
	{
		BitArray<numberOfArrayElements, 17> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 131071);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(131071, bitArray.Get(i));
		}
	}

	// Nineteen teen bits per element
	{
		BitArray<numberOfArrayElements, 19> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 524287);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(524287, bitArray.Get(i));
		}
	}

	// Twenty-one teen bits per element
	{
		BitArray<numberOfArrayElements, 21> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 2097147);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(2097147, bitArray.Get(i));
		}
	}

	// Twenty-three teen bits per element
	{
		BitArray<numberOfArrayElements, 23> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 8388591);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(8388591, bitArray.Get(i));
		}
	}

	// Twenty-five teen bits per element
	{
		BitArray<numberOfArrayElements, 25> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 33554367);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(33554367, bitArray.Get(i));
		}
	}

	// Twenty-seven teen bits per element
	{
		BitArray<numberOfArrayElements, 27> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 134217471);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(134217471, bitArray.Get(i));
		}
	}

	// Twenty-nine teen bits per element
	{
		BitArray<numberOfArrayElements, 29> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 536869887);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(536869887, bitArray.Get(i));
		}
	}

	// Thirty-one teen bits per element
	{
		BitArray<numberOfArrayElements, 31> bitArray;

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			bitArray.Set(i, 2147479551);
		}

		for (int i = 0; i < numberOfArrayElements; ++i)
		{
			EXPECT_EQ(2147479551, bitArray.Get(i));
		}
	}
}


TEST_F(BitArray_static_test, Truncating_set_bits)
{
	constexpr unsigned numberOfArrayElements = 25;

	BitArray<numberOfArrayElements, 4> bitArray;

	// 0b101010 which is 42 should be truncated to 0b1010 which is 10
	bitArray.Set(0, 42);

	// 0b100111 should be truncated to 0b0111
	bitArray.Set(1, 0b100111);

	// 0b101100 which is 42 should be truncated to 12
	bitArray.Set(2, 44);

	// 16 which is 0b10000 should be truncated to 0
	bitArray.Set(3, 16);

	// Set the last value for test to the last element if array 31 should be truncated to 15
	bitArray.Set(24, 31);

	// Check the values
	EXPECT_EQ(10, bitArray.Get(0));
	EXPECT_EQ(7, bitArray.Get(1));
	EXPECT_EQ(12, bitArray.Get(2));
	EXPECT_EQ(0, bitArray.Get(3));
	EXPECT_EQ(15, bitArray.Get(24));
}


TEST_F(BitArray_static_test, Random_insertion_test)
{
	constexpr unsigned numberOfArrayElements = 100;

	BitArray<numberOfArrayElements, 11> bitArray;

	bitArray.Set(0, 23);
	bitArray.Set(1, 2047);
	bitArray.Set(34, 57);
	bitArray.Set(56, 0);
	bitArray.Set(71, 23);
	bitArray.Set(72, 512);
	bitArray.Set(73, 228);
	bitArray.Set(74, 947);
	bitArray.Set(75, 1689);

	// Check the values
	EXPECT_EQ(23, bitArray.Get(0));
	EXPECT_EQ(2047, bitArray.Get(1));
	EXPECT_EQ(57, bitArray.Get(34));
	EXPECT_EQ(0, bitArray.Get(56));
	EXPECT_EQ(23, bitArray.Get(71));
	EXPECT_EQ(512, bitArray.Get(72));
	EXPECT_EQ(228, bitArray.Get(73));
	EXPECT_EQ(947, bitArray.Get(74));
	EXPECT_EQ(1689, bitArray.Get(75));
}


TEST_F(BitArray_static_test, Special_functions)
{
	constexpr unsigned numberOfArrayElements = 100;

	BitArray<numberOfArrayElements, 11> bitArray;

	// Set the values on "bitArray"
	bitArray.Set(0, 23);
	bitArray.Set(1, 2047);
	bitArray.Set(34, 57);
	bitArray.Set(56, 0);
	bitArray.Set(71, 23);
	bitArray.Set(72, 512);
	bitArray.Set(73, 228);
	bitArray.Set(74, 947);
	bitArray.Set(75, 1689);

	// Check the values in "bitArray"
	EXPECT_EQ(23, bitArray.Get(0));
	EXPECT_EQ(2047, bitArray.Get(1));
	EXPECT_EQ(57, bitArray.Get(34));
	EXPECT_EQ(0, bitArray.Get(56));
	EXPECT_EQ(23, bitArray.Get(71));
	EXPECT_EQ(512, bitArray.Get(72));
	EXPECT_EQ(228, bitArray.Get(73));
	EXPECT_EQ(947, bitArray.Get(74));
	EXPECT_EQ(1689, bitArray.Get(75));

	// Testing copy constructor, as this will invoke copy constructor generated by the compiler
	BitArray<numberOfArrayElements, 11> secondBitArray = bitArray;

	// Check the values in "secondBitArray" those values should be the same as in "bitArray"
	EXPECT_EQ(23, secondBitArray.Get(0));
	EXPECT_EQ(2047, secondBitArray.Get(1));
	EXPECT_EQ(57, secondBitArray.Get(34));
	EXPECT_EQ(0, secondBitArray.Get(56));
	EXPECT_EQ(23, secondBitArray.Get(71));
	EXPECT_EQ(512, secondBitArray.Get(72));
	EXPECT_EQ(228, secondBitArray.Get(73));
	EXPECT_EQ(947, secondBitArray.Get(74));
	EXPECT_EQ(1689, secondBitArray.Get(75));

	// Create "thirdBitArray" variable and test copy assignment
	BitArray<numberOfArrayElements, 11> thirdBitArray;

	for (int i = 0; i < numberOfArrayElements; ++i)
	{
		bitArray.Set(i, 2047);
	}

	for (int i = 0; i < numberOfArrayElements; ++i)
	{
		EXPECT_EQ(2047, bitArray.Get(i));
	}

	thirdBitArray = secondBitArray;

	// Check the values in "thirdBitArray" after secondBitArray assignment
	EXPECT_EQ(23, thirdBitArray.Get(0));
	EXPECT_EQ(2047, thirdBitArray.Get(1));
	EXPECT_EQ(57, thirdBitArray.Get(34));
	EXPECT_EQ(0, thirdBitArray.Get(56));
	EXPECT_EQ(23, thirdBitArray.Get(71));
	EXPECT_EQ(512, thirdBitArray.Get(72));
	EXPECT_EQ(228, thirdBitArray.Get(73));
	EXPECT_EQ(947, thirdBitArray.Get(74));
	EXPECT_EQ(1689, thirdBitArray.Get(75));
}


TEST_F(BitArray_static_test, Assigning_return_value_of_opeartor_subscript)
{
	BitArray<10, 2> arrayObject;

	arrayObject.Set(2, 1);

	int a = arrayObject[2];

	EXPECT_EQ(1, a);
}


TEST_F(BitArray_static_test, Modifying_subscripted_element)
{
	BitArray<10, 2> arrayObject;
	arrayObject[6] = 2;

	EXPECT_EQ(2, arrayObject.Get(6));
}
