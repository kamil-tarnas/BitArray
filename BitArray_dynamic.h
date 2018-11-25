#ifndef BIT_ARRAY_DYNAMIC
#define BIT_ARRAY_DYNAMIC

/*
 * This must be done in run-time if we want to decide the size of array at the run-time
 */

// Internal manual storage member variable
// Template partial specialization for internal data_p manual storage BitArray instances
template<>
class BitArray<>
{
public:
	BitArray() = delete;
	BitArray(unsigned sizeOfArray, unsigned sizeOfElement);
	BitArray(const BitArray<>&);
	BitArray<>& operator=(BitArray<> rhs);
	~BitArray();

	unsigned Get(unsigned position);
	void Set(unsigned position, unsigned value);

	// Should return some internal helper type to avoid returning reference to whole word
	unsigned operator[](unsigned position) = delete;

protected:

private:
	unsigned* data_p;
	unsigned sizeOfArray;
	unsigned sizeOfElement;
};


BitArray<>::BitArray(unsigned sizeOfArray, unsigned sizeOfElement) :
				   data_p(nullptr),
				   sizeOfArray(sizeOfArray),
				   sizeOfElement(sizeOfElement)
{
	data_p = new unsigned[CaculateInternalArraySize(sizeOfArray, sizeOfElement)];
}


BitArray<>::BitArray(const BitArray<>& rhs) :
			data_p(new unsigned[CaculateInternalArraySize(rhs.sizeOfArray, rhs.sizeOfElement)]),
			sizeOfArray(rhs.sizeOfArray),
			sizeOfElement(rhs.sizeOfElement)
{
	//Measure this versus memcpy function, local var for loop end condttion
	for (unsigned i = 0; i < CaculateInternalArraySize(rhs.sizeOfArray, rhs.sizeOfElement); ++i)
	{
		data_p[i] = rhs.data_p[i];
	}
}


BitArray<>& BitArray<>::operator=(BitArray<> rhs)
{
	//Delete the original storage
	delete data_p;

	//Swap pointers
	data_p = rhs.data_p;
	sizeOfArray = rhs.sizeOfArray;
	sizeOfElement = rhs.sizeOfElement;

	/* Note, that the original storage data_p could be deleted by temporary rhs object destructor
	 * when swapping ptrs
	 */

	//Set the data_p to nullptr to not destroy data_p this as they point to the same storage
	rhs.data_p = nullptr;

	return *this;
}


BitArray<>::~BitArray()
{
	delete data_p;
}


unsigned BitArray<>::Get(unsigned position)
{
	/*
	 * Probably these computations could be put in separate inline function, as they will
	 * be calculated many times in many different functions
	 */

	// The number of entries in word, in one element of "data_p" member variable array
	const unsigned amountOfEntriesPerWord = (sizeof(unsigned) * CHAR_BITS) / sizeOfElement;

	// The position of word containing entry in "data_p" member variable
	const unsigned wordPositionInArray = position / amountOfEntriesPerWord;

	// Relative position of entry in certain word, starting from zero, given in entries
	const unsigned entryOffsetInWord = position - (wordPositionInArray * amountOfEntriesPerWord);

	// Calculate the bit shift size, how much bits do we shift?
	const unsigned bitShiftSize = sizeOfElement * (amountOfEntriesPerWord - 1 - entryOffsetInWord);

	// Calculate bit mask for further operations
	const unsigned mask = ((1U << sizeOfElement) - 1);

	/*
	 * Getting the value of entry
	 * Could it be optimized when indexing starts from least significant bits?
	 */

	// Return the bits of entry, they are located starting from MSB, so shifting right is required
	// Mask for returned bits, bits that are not the part of entry will be cleared
	return data_p[wordPositionInArray] >> bitShiftSize & mask;
}


void BitArray<>::Set(unsigned position, unsigned value)
{
	/*
	 * Probably these computations could be put in separate inline function, as they will
	 * be calculated many times in many different functions
	 */

	// The number of entries in word, in one element of "data_p" member variable array
	const unsigned amountOfEntriesPerWord = (sizeof(unsigned) * CHAR_BITS) / sizeOfElement;

	// The position of word containing entry in "data_p" member variable
	const unsigned wordPositionInArray = position / amountOfEntriesPerWord;

	// Relative position of entry in certain word, starting from zero, given in entries
	const unsigned entryOffsetInWord = position - (wordPositionInArray * amountOfEntriesPerWord);

	// Calculate the bit shift size, how much bits do we shift?
	const unsigned bitShiftSize = sizeOfElement * (amountOfEntriesPerWord - 1 - entryOffsetInWord);

	// Calculate bit mask for further operations
	const unsigned mask = ((1U << sizeOfElement) - 1);

	/*
	 * Setting the value of entry
	 */

	// Truncate the bits of value which are at greater positions than sizeOfElemet -1
	// This ensures that we will not overwrite value of another entries
	value &= mask;

	// Get bits in value to be set in the right place in word
	value <<= bitShiftSize;

	// Clear the bits corresponding to occupied in new entry in "data_p" array
	data_p[wordPositionInArray] &= ~mask << bitShiftSize;

	// Make bitwise "or" operation to merge bits of value moved to the right place
	// with the rest of bits of word, that won't be modified
	data_p[wordPositionInArray] |= value;
}

#endif //#ifndef BIT_ARRAY_DYNAMIC
