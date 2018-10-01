#ifndef BIT_ARRAY_STATIC
#define BIT_ARRAY_STATIC

// Internal automatic storage member variable
// Template partial specialization for internal data automatic storage BitArray instances
template<unsigned sizeOfArray, unsigned sizeOfElement>
class BitArray<sizeOfArray, sizeOfElement>
{
public:
	unsigned Get(unsigned position);
	void Set(unsigned position, unsigned value);

	// Should return some internal helper type to avoid returning reference to whole word
	unsigned operator[](unsigned position) = delete;

protected:

private:
	unsigned data[CaculateInternalArraySize(sizeOfArray, sizeOfElement)];

	/*
	 * For helper class BitArrayElemRefHelper those variable have to be visible, make
	 * a friend class or think of something similar
	 */

	// The number of entries in word, in one element of "data" member variable array
	static constexpr unsigned amountOfEntriesPerWord =
													(sizeof(unsigned) * CHAR_BITS) / sizeOfElement;
	// Get the padding value
	static constexpr unsigned paddingBits =
											(sizeof(unsigned) * CHAR_BITS) -
											(sizeOfElement * amountOfEntriesPerWord);
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

	// The position of word containing entry in "data" member variable
	const unsigned wordPositionInArray = position / amountOfEntriesPerWord;

	// Relative position of entry in certain word, starting from zero, given in entries
	const unsigned entryOffsetInWord = position - (wordPositionInArray * amountOfEntriesPerWord);

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


//Proxy class for returning references to elements in BitArray class instances
template<template<unsigned sizeOfArray, unsigned sizeOfElement> typename BitArrayTemplate>
class BitArrayElemRefHelper
{
   /*
    * Class should hold reference or pointer to whole word containing
    * desired array element - the specific bits in referenced word.
    * Class should modify the desired bits according to specific behaviour.
    *
    * Problematic might be assigning this varaible to element of array of template class BitArray
    * Therefore we should always operate on this type (BitArrayElemRefHelper) and only cast to other types -
    * the real ones, like int or unsigned - when assiging from this type. So here should be
    * type cast defined.
    */


   /* How this would work?
    * BitArray someArray;
    * someArray[3] (this would return an object of BitArrayElemRefHelper class)
    *
    * Typical use case would be
    *
    * someArray[3] = 4;
    * Here we should define implicit conversion from int to BitArrayElemRefHelper
    * and do an operation of assigning this int to specific word in BitArray instance
    *
    */

    //CONVERTING CONSTRUCTOR

    //The constructor can take only one integer and it will be okay,
    //The problems are conversions from int to unsigned
    //And copy assignment operator
    //
    //Operator [] should return most information, that is the reference of word?
    public:
       BitArrayElemRefHelper(unsigned assignment)
       {
    	   // We already have the referenced word?
    	   // No, we should calculate it here, based on desired returning elem?
    	   // Or we should construct BitArrayElemRefHelper instance with specific knowledge
    	   // of the position of referenced element?

    		/*
    		 * Probably these computations could be put in separate inline function, as they will
    		 * be calculated many times in many different functions
    		 */


    	   /*
    	    * HOW TO GET TO PARAMETER TEMPLATE VALUES FROM OTEHR CLASS?
    	    * AMOUNT OF ENTRIES AND SO ON values could be held on some static
    	    * variable, some const static variable, or event constexpr static variable
    	    *
    	    * getting to that value might be costly though?
    	    *
    	    * but how to get to different temlatizations of the same class
    	    * we should have the possiblity of getting different parameters (for example:
    	    * sizeOfElement) for different templatization of BitArray
    	    *
    	    * This should be a template, which takes template as its template argument
    	    */

    		// Calculate the bit shift size, how much bits do we shift?
    		const unsigned bitShiftSize = BitArrayTemplate<sizeOfArray, sizeOfElement>::sizeOfElement * (amountOfEntriesPerWord - 1 - elementOffset)
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
    		refWord &= ~mask << bitShiftSize;

    		// Make bitwise "or" operation to merge bits of value moved to the right place
    		// with the rest of bits of word, that won't be modified
    		refWord |= value;

       }

       // Another constructor, which most preferably should be called only from BitArray class
       // Private constructor, which is a friend function for BitArray class?
       BitArrayElemRefHelper(unsigned elementOffset,
							 unsigned& referencedWord)
       {
    	   refWord = &referencedWord;
    	   elementOffset = elementOffset;
       }

    protected:
    private:

    //Pointer or reference - decide!
    unsigned& refWord;
    unsigned elementOffset;

    //What information do we need here?
    //Trying to make this object as lightweighted as possible
};


// Argument for opeartor[] should be int to avoid representation changing conversion
//TODO: This should be declared after BitArrayElemRefHelper, because its definition
// 		must be known before return value instantiation of its object
template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArrayElemRefHelper<BitArray<sizeOfArray, sizeOfElement>>
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

	return BitArrayElemRefHelper<BitArray<sizeOfArray, sizeOfElement>
						(entryOffsetInWord, data[wordPositionInArray]);
}


#endif //#ifndef BIT_ARRAY_STATIC
