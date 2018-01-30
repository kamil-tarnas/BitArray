#ifndef BIT_ARRAY_UTILS
#define BIT_ARRAY_UTILS

//TODO: Temporary, remove after including proper header
#define CHAR_BITS 8

constexpr unsigned CaculateInternalArraySize(unsigned sizeOfArray, unsigned sizeOfElement) noexcept;

void CopyArrayElements(unsigned* source, unsigned* destination, unsigned numberOfElements);

constexpr unsigned CaculateInternalArraySize(unsigned sizeOfArray, unsigned sizeOfElement) noexcept
{
	/*
	 * Get the number of elements that will fit on one word, then divide the sizeOfArray by
	 * that number and take the ceiling of it
	 */
	return (sizeOfArray + ((sizeof(unsigned) * CHAR_BITS) / sizeOfElement) - 1) /
		   ((sizeof(unsigned) * CHAR_BITS) / sizeOfElement);
}

void CopyArrayElements(unsigned* source, unsigned* destination, unsigned numberOfElements);

//TODO: Size of array is needed, size in bits of element is needed
template<unsigned ...>
class BitArray
{
	//No need to implement this, all cases are covered by template specializations
};

#endif //#ifndef BIT_ARRAY_UTILS
