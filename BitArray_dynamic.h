#ifndef BIT_ARRAY_DYNAMIC
#define BIT_ARRAY_DYNAMIC

//TODO:Investigate the code bloat for this template, passing of size argument could be done
//in run-time, there is no need to generate code for every occurrence of different size template
//argument value

//Internal manual storage member variable
//Template partial specialization for internal data manual storage BitArray instances
template<unsigned sizeOfArray, unsigned sizeOfElement>
class BitArray<sizeOfArray, sizeOfElement, true>
{
public:
protected:
private:
};

#endif //#ifndef BIT_ARRAY_DYNAMIC
