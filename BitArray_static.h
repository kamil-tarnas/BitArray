#ifndef BIT_ARRAY_STATIC
#define BIT_ARRAY_STATIC

//Internal automatic storage member variable
//Template partial specialization for internal data automatic storage BitArray instances
template<unsigned sizeOfArray, unsigned sizeOfElement>
class BitArray<sizeOfArray, sizeOfElement, false>
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
	//The storage for array elements
//	unsigned data[((sizeOfArray * sizeOfElement) +
//			       (sizeof(unsigned) * CHAR_BITS) - 1) /
//				   (sizeof(unsigned) * CHAR_BITS)];
	unsigned data[CaculateInternalArraySize(sizeOfArray, sizeOfElement)];
};

template<unsigned sizeOfArray, unsigned sizeOfElement>
unsigned BitArray<sizeOfArray, sizeOfElement, false>::Get(unsigned position)
{
	//TODO: Write!
	return 5;
}

template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArray<sizeOfArray, sizeOfElement, false>::~BitArray()
{
}

template<unsigned sizeOfArray, unsigned sizeOfElement>
BitArray<sizeOfArray, sizeOfElement, false>::BitArray()
{
}

#endif //#ifndef BIT_ARRAY_STATIC
