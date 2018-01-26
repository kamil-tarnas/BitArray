#ifndef BIT_ARRAY_UTILS
#define BIT_ARRAY_UTILS

//TODO: Temporary, remove after including proper header
#define CHAR_BITS 8

constexpr unsigned CaculateInternalArraySize(unsigned sizeOfArray, unsigned sizeOfElement)
{
	return (((sizeOfArray * sizeOfElement) +
		     (sizeof(unsigned) * CHAR_BITS) - 1) /
			 (sizeof(unsigned) * CHAR_BITS));
}

//TODO: Size of array is needed, size in bits of element is needed
template<unsigned sizeOfArray, unsigned sizeOfElement, bool manualStorage>
class BitArray
{
	//No need to implement this, all cases are covered by template specializations
};

#endif //#ifndef BIT_ARRAY_UTILS
