#ifndef BIT_ARRAY_ELEM_REF_HEPLER
#define BIT_ARRAY_ELEM_REF_HEPLER

//This can be befiriended with the main BitArray class
//Proxy class for returning references to elements in BitArray class instances
// TODO: Make a template that could cover dynamic version of EleRefHelper
template<unsigned sizeOfArray, unsigned sizeOfElement>
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
	//Constructor can be defined in private part of accessibility, befriending this class
	//with BitArray will guarantee possibility of accessing this constructor and will
	//prevent creating an object of this class in another circumstances
    public:

    //Need to be implicit
	//Also needs to be public, you cannot befriend it in unsigned type class declaration, there is
	//no such declaration xD
    operator unsigned();

    //Moved to public section temporairly
    // Analyse if returning reference to ElemRefHelper class is the best way of impelenting this
    BitArrayElemRefHelper& operator=(unsigned assignment);

    protected:

    private:

	// Object of type BitArrayElemRefHelper should be instantiated only by BitArray class
    BitArrayElemRefHelper(unsigned assignment);
    /*
     * = operator shall be defined for this class, it will be used when assigning through the
     * proxy object to underlying storage in the main BitArray class
     */

    // Another constructor, which most preferably should be called only from BitArray class
    // Private constructor, which is a friend function for BitArray class?
    // Object of type BitArrayElemRefHelper should be instantiated only by BitArray class
    BitArrayElemRefHelper(unsigned elementOffset, unsigned& referencedWord);

    //Is this really needed? How can we make this object as lightweight as possible?
    unsigned elementOffset;

    //Pointer or reference - decide!
    unsigned& refWord; //Must be initialized in constructor initializer list
    
    //Befriend the main class, template parameters cannot shadow each other, give non-type
    //template parameters some new names
    friend class BitArray<sizeOfArray, sizeOfElement>;

    //What information do we need here?
    //Trying to make this object as lightweighted as possible
};

//This is not the constructor case for operator[] in BitArray
template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArrayElemRefHelper<sizeOfArray, sizeOfElement>::
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
	const unsigned bitShiftSize = sizeOfElement *
		  (BitArray<sizeOfArray, sizeOfElement>::amountOfEntriesPerWord - 1 - elementOffset);

	// Calculate bit mask for further operations
	const unsigned mask = ((1U << sizeOfElement) - 1);

	/*
	 * Setting the value of entry
	 */

	// Truncate the bits of value which are at greater positions than sizeOfElemet -1
	// This ensures that we will not overwrite value of another entries in array
	assignment &= mask;

	// Get bits in value to be set in the right place in word
	assignment <<= bitShiftSize;

	// Clear the bits corresponding to occupied in new entry in "data" array
	refWord &= ~mask << bitShiftSize;

	// Make bitwise "or" operation to merge bits of value moved to the right place
	// with the rest of bits of word, that won't be modified
	refWord |= assignment;
}

// Used by BitArray::operator[]
template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArrayElemRefHelper<sizeOfArray, sizeOfElement>::
BitArrayElemRefHelper(unsigned elementOffset, unsigned& referencedWord) :
	 elementOffset(elementOffset), refWord(referencedWord)
{
	// All is done in constructor member initializer list
}

// Used to convert ElemRefHelper to unsigned type
template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArrayElemRefHelper<sizeOfArray, sizeOfElement>::
operator unsigned()
{
	/*
	 * Probably these computations could be put in separate inline function, as they will
	 * be calculated many times in many different functions
	 */

	// Calculate the bit shift size, how much bits do we shift?
	const unsigned bitShiftSize = sizeOfElement *
		  (BitArray<sizeOfArray, sizeOfElement>::amountOfEntriesPerWord - 1 - elementOffset);

	// Calculate bit mask for further operations
	const unsigned mask = ((1U << sizeOfElement) - 1);

	/*
	 * Getting the value of entry
	 * Could it be optimized when indexing starts from least significant bits?
	 */

	// Return the bits of entry, they are located starting from MSB, so shifting right is required
	// Mask for returned bits, bits that are not the part of entry will be cleared
	return refWord >> bitShiftSize & mask;
}


template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArrayElemRefHelper<sizeOfArray, sizeOfElement>&
BitArrayElemRefHelper<sizeOfArray, sizeOfElement>::
operator=(unsigned assignment)
{
	/*
	 * Should this do exactly the same as converting constructor?
	 */

	// Calculate the bit shift size, how much bits do we shift?
	const unsigned bitShiftSize = sizeOfElement *
			(BitArray<sizeOfArray, sizeOfElement>::amountOfEntriesPerWord - 1 - elementOffset);

	// Calculate bit mask for further operations
	const unsigned mask = ((1U << sizeOfElement) - 1);

	/*
	 * Setting the value of entry
	 */

	// Truncate the bits of value which are at greater positions than sizeOfElemet -1
	// This ensures that we will not overwrite value of another entries in array
	assignment &= mask;

	// Get bits in value to be set in the right place in word
	assignment <<= bitShiftSize;

	// Clear the bits corresponding to occupied in new entry in "data" array
	refWord &= ~mask << bitShiftSize;

	// Make bitwise "or" operation to merge bits of value moved to the right place
	// with the rest of bits of word, that won't be modified
	refWord |= assignment;

	return *this;
}


#endif //#ifndef BIT_ARRAY_ELEM_REF_HEPLER
