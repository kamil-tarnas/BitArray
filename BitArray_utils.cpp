#include "BitArray_utils.h"

void CopyArrayElements(unsigned* source, unsigned* destination, unsigned numberOfElements)
{
	for (unsigned i = 0; i < numberOfElements; ++i)
	{
		destination[i] = source[i];
	}
}
