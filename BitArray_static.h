#ifndef BIT_ARRAY_STATIC
#define BIT_ARRAY_STATIC

#include "BitArrayElemRefHelper.h"

// Internal automatic storage member variable
// Template partial specialization for internal data automatic storage BitArray instances
template<unsigned sizeOfArray, unsigned sizeOfElement>
class BitArray<sizeOfArray, sizeOfElement>
{
public:
	unsigned Get(unsigned position);
	void Set(unsigned position, unsigned value);

	// Should return some internal helper type to avoid returning reference to whole word
	BitArrayElemRefHelper<sizeOfArray, sizeOfElement> operator[](unsigned position);

protected:

private:
	unsigned data[CaculateInternalArraySize(sizeOfArray, sizeOfElement)];

	/*
	 * For helper class BitArrayElemRefHelper those variable have to be visible, make
	 * a friend class or think of something similar
	 */

	// The number of entries in word, in one element of "data" member variable array
	static constexpr unsigned amountOfEntriesPerWord = (sizeof(unsigned) * CHAR_BITS) /
														sizeOfElement;
	// Get the padding value
	static constexpr unsigned paddingBits = (sizeof(unsigned) * CHAR_BITS) -
											(sizeOfElement * amountOfEntriesPerWord);

	// Calculate bit mask for truncating operations
	static constexpr unsigned mask = ((1U << sizeOfElement) - 1);

	//Befriend helper class, template parameters cannot shadow each other, give non-type
    //template parameters some new names
	friend class BitArrayElemRefHelper<sizeOfArray, sizeOfElement>;
};


template<unsigned sizeOfArray, unsigned sizeOfElement>
unsigned BitArray<sizeOfArray, sizeOfElement>::Get(unsigned position)
{
	/*
	 * Probably these computations could be put in separate inline function, as they will
	 * be calculated many times in many different functions
	 */

	// The position of word containing entry in "data" member variable
	const unsigned wordPositionInArray = position / amountOfEntriesPerWord;

	// Relative position of entry in certain word, starting from zero, given in entries
	const unsigned entryOffsetInWord = position - (wordPositionInArray * amountOfEntriesPerWord);

	// Calculate the bit shift size, how much bits do we shift?
	const unsigned bitShiftSize = sizeOfElement * (amountOfEntriesPerWord - 1 - entryOffsetInWord)
			             + paddingBits;

	/*
	 * Getting the value of entry
	 * Could it be optimized when indexing starts from least significant bits?
	 */

	// Return the bits of entry, they are located starting from MSB, so shifting right is required
	// Mask for returned bits, bits that are not the part of entry will be cleared
	return data[wordPositionInArray] >> bitShiftSize & mask;
}


template<unsigned sizeOfArray, unsigned sizeOfElement>
void BitArray<sizeOfArray, sizeOfElement>::Set(unsigned position, unsigned value)
{
	/*
	 * Probably these computations could be put in separate inline function, as they will
	 * be calculated many times in many different functions
	 */

	// The position of word containing entry in "data" member variable
	const unsigned wordPositionInArray = position / amountOfEntriesPerWord;

	// Relative position of entry in certain word, starting from zero, given in entries
	const unsigned entryOffsetInWord = position - (wordPositionInArray * amountOfEntriesPerWord);

	// Calculate the bit shift size, how much bits do we shift?
	const unsigned bitShiftSize = sizeOfElement * (amountOfEntriesPerWord - 1 - entryOffsetInWord)
			             + paddingBits;


	/*
	 * Setting the value of entry
	 */

	// Truncate the bits of value which are at greater positions than sizeOfElemet -1
	// This ensures that we will not overwrite value of another entries in array
	value &= mask;

	// Get bits in value to be set in the right place in word
	value <<= bitShiftSize;

	// Clear the bits corresponding to occupied in new entry in "data" array
	data[wordPositionInArray] &= ~mask << bitShiftSize;

	// Make bitwise "or" operation to merge bits of value moved to the right place
	// with the rest of bits of word, that won't be modified
	data[wordPositionInArray] |= value;
}


// Argument for operator[] should be int to avoid representation changing conversion
//TODO: This should be declared after BitArrayElemRefHelper, because its definition
// 		must be known before return value instantiation of its object
template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArrayElemRefHelper<sizeOfArray, sizeOfElement>
BitArray<sizeOfArray, sizeOfElement>::operator[](unsigned position)
{
	/*
	 * Probably these computations could be put in separate inline function, as they will
	 * be calculated many times in many different functions
	 */

	// The number of entries in word, in one element of "data" member variable array
	constexpr unsigned amountOfEntriesPerWord = (sizeof(unsigned) * CHAR_BITS) / sizeOfElement;

	// The position of word containing entry in "data" member variable
	const unsigned wordPositionInArray = position / amountOfEntriesPerWord;

	// Relative position of entry in certain word, starting from zero, given in entries
	const unsigned entryOffsetInWord = position - (wordPositionInArray * amountOfEntriesPerWord);

	return BitArrayElemRefHelper<sizeOfArray, sizeOfElement>
								(entryOffsetInWord, data[wordPositionInArray]);
}


#endif //#ifndef BIT_ARRAY_STATIC
