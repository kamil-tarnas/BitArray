#ifndef BIT_ARRAY_STATIC
#define BIT_ARRAY_STATIC

// Internal automatic storage member variable
// Template partial specialization for internal data automatic storage BitArray instances
template<unsigned sizeOfArray, unsigned sizeOfElement>
class BitArray<sizeOfArray, sizeOfElement>
{
public:
	BitArray();
	BitArray(const BitArray<sizeOfArray, sizeOfElement>&);
	BitArray<sizeOfArray, sizeOfElement>& operator=(const BitArray<sizeOfArray, sizeOfElement>&);
	~BitArray();

	unsigned Get(unsigned position);
	void Set(unsigned position, unsigned value);

	// Should return some internal helper type to avoid returning reference to whole word
	unsigned operator[](unsigned position) = delete;

protected:

private:
	unsigned data[CaculateInternalArraySize(sizeOfArray, sizeOfElement)];
};


template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArray<sizeOfArray, sizeOfElement>::BitArray()
{
}


template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArray<sizeOfArray, sizeOfElement>::~BitArray()
{
}


template<unsigned sizeOfArray, unsigned sizeOfElement>
unsigned BitArray<sizeOfArray, sizeOfElement>::Get(unsigned position)
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

	// Get the padding value
	constexpr unsigned paddingBits = (sizeof(unsigned) * CHAR_BITS) -
								 (sizeOfElement * amountOfEntriesPerWord);

	// Calculate the bit shift size, how much bits do we shift?
	const unsigned bitShiftSize = sizeOfElement * (amountOfEntriesPerWord - 1 - entryOffsetInWord)
			             + paddingBits;

	// Calculate bit mask for further operations
	const unsigned mask = ((1U << sizeOfElement) - 1);

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

	// The number of entries in word, in one element of "data" member variable array
	constexpr unsigned amountOfEntriesPerWord = (sizeof(unsigned) * CHAR_BITS) / sizeOfElement;

	// The position of word containing entry in "data" member variable
	const unsigned wordPositionInArray = position / amountOfEntriesPerWord;

	// Relative position of entry in certain word, starting from zero, given in entries
	const unsigned entryOffsetInWord = position - (wordPositionInArray * amountOfEntriesPerWord);

	// Get the padding value
	constexpr unsigned paddingBits = (sizeof(unsigned) * CHAR_BITS) -
								 (sizeOfElement * amountOfEntriesPerWord);

	// Calculate the bit shift size, how much bits do we shift?
	const unsigned bitShiftSize = sizeOfElement * (amountOfEntriesPerWord - 1 - entryOffsetInWord)
			             + paddingBits;

	// Calculate bit mask for further operations
	const unsigned mask = ((1U << sizeOfElement) - 1);

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

#endif //#ifndef BIT_ARRAY_STATIC
