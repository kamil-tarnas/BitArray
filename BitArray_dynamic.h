#ifndef BIT_ARRAY_DYNAMIC
#define BIT_ARRAY_DYNAMIC

//TODO:Investigate the code bloat for this template, passing of size argument could be done
//in run-time, there is no need to generate code for every occurrence of different size template
//argument value

//Internal manual storage member variable
//Template partial specialization for internal data_p manual storage BitArray instances
template<unsigned sizeOfArray, unsigned sizeOfElement>
class BitArray<sizeOfArray, sizeOfElement, true>
{
public:
	BitArray();
	BitArray(const BitArray<sizeOfArray, sizeOfElement, false>&);
	BitArray<sizeOfArray, sizeOfElement, false>&
		operator=(const BitArray<sizeOfArray, sizeOfElement, false>&);
	~BitArray();

	unsigned Get(unsigned position);
	void Set(unsigned position, unsigned value);

	//Have to return reference to unsigned, it must fit the variable you are assigning
	//Or reference to a bitfield? Can it be done?
	unsigned operator[](unsigned position) = delete;
protected:
private:
	unsigned* data_p;
};


template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArray<sizeOfArray, sizeOfElement, true>::BitArray() : data_p(nullptr)
{
	data_p = new unsigned[sizeOfArray];
}


template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArray<sizeOfArray, sizeOfElement, true>::~BitArray()
{
	delete data_p;
}


template<unsigned sizeOfArray, unsigned sizeOfElement>
unsigned BitArray<sizeOfArray, sizeOfElement, true>::Get(unsigned position)
{
	/*
	 * Probably these computations could be put in separate inline function, as they will
	 * be calculated many times in many different functions
	 */

	//The number of entries in word, in one element of "data_p" member variable array
	const unsigned amountOfEntriesPerWord = (sizeof(unsigned) * CHAR_BITS) / sizeOfElement;

	//The position of word containing entry in "data_p" member variable
	const unsigned wordPositionInArray = position / amountOfEntriesPerWord;

	//Relative position of entry in certain word, starting from zero, given in entries
	const unsigned entryOffsetInWord = position - (wordPositionInArray * amountOfEntriesPerWord);

	//Get the padding value
	const unsigned paddingBits = (sizeof(unsigned) * CHAR_BITS) -
								 (sizeOfElement * amountOfEntriesPerWord);

	/*
	 * Getting the value of entry
	 * Could it be optimized when indexing starts from least significant bits?
	 */

	//Bits to shift depend on element index and bitsPerEnty value, there is max shift to right in U32 word
	const unsigned bitsToShift = ((amountOfEntriesPerWord - 1 - entryOffsetInWord) * sizeOfElement)
								   + paddingBits;

	//Return the bits of entry, they are located starting from MSB, so shifting right is required
	//Mask for returned bits, bits that are not the part of entry will be cleared
	//TODO: Measure bit shift versus ^ operator performance
	return data_p[wordPositionInArray] >> bitsToShift & (unsigned)((1U << sizeOfElement) - 1);
}

template<unsigned sizeOfArray, unsigned sizeOfElement>
void BitArray<sizeOfArray, sizeOfElement, true>::Set(unsigned position, unsigned value)
{
	/*
	 * Probably these computations could be put in separate inline function, as they will
	 * be calculated many times in many different functions
	 */

	//The number of entries in word, in one element of "data_p" member variable array
	const unsigned amountOfEntriesPerWord = (sizeof(unsigned) * CHAR_BITS) / sizeOfElement;

	//The position of word containing entry in "data_p" member variable
	const unsigned wordPositionInArray = position / amountOfEntriesPerWord;

	//Relative position of entry in certain word, starting from zero, given in entries
	const unsigned entryOffsetInWord = position - (wordPositionInArray * amountOfEntriesPerWord);

	//Get the padding value
	const unsigned paddingBits = (sizeof(unsigned) * CHAR_BITS) -
								 (sizeOfElement * amountOfEntriesPerWord);

	/*
	 * Setting the value of entry
	 */

	//Truncate the bits of value which are at greater positions than sizeOfElemet -1
	//This ensures that we will not overwrite value of another entries
	value &= (unsigned)((1U << sizeOfElement) - 1);

	//Get bits in value to be set in the right place in word
	value <<= (sizeOfElement * (amountOfEntriesPerWord - 1 - entryOffsetInWord) + paddingBits);

	//Clear the bits corresponding to occupied in new entry in "data_p" array
	data_p[wordPositionInArray] &= ~((((1U << sizeOfElement) - 1) <<
			(sizeOfElement * (amountOfEntriesPerWord - 1 - entryOffsetInWord) + paddingBits)));

	//Make bitwise "or" operation to merge bits of value moved to the right place
	//with the rest of bits of word, that won't be modified
	data_p[wordPositionInArray] |= value;
}

#endif //#ifndef BIT_ARRAY_DYNAMIC
