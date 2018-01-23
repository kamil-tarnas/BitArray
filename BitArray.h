#ifndef BIT_ARRAY
#define BIT_ARRAY

//TODO: Size of array is needed, size in bits of element is needed
template<unsigned size, bool manualStorage>
class BitArray
{
	//No need to implement this, all cases are covered by template specializations
};

//Internal automatic storage member variable
//Template partial specialization for internal data automatic storage BitArray instances
template<unsigned size>
class BitArray<size, false>
{
public:
protected:
private:
	//unsigned data[sizeof]
};


//TODO:Investigate the code bloat for this template, passing of size argument could be done
//in run-time, there is no need to generate code for every occurrence of different size template
//argument value

//Internal manual storage member variable
//Template partial specialization for internal data manual storage BitArray instances
template<unsigned size>
class BitArray<size, true>
{
public:
protected:
private:
};

#endif //#ifndef BIT_ARRAY
