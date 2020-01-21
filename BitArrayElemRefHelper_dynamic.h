#ifndef BIT_ARRAY_ELEM_REF_HEPLER_DYNAMIC
#define BIT_ARRAY_ELEM_REF_HEPLER_DYNAMIC

//No namespace management in this project realy
namespace dynamic
{
	// Does this need to be a template? What would be the use cases of template instances?
	class BitArrayElemRefHelper
	{
		//TODO: What could be declared as private?
	public:
		// Constructors? Befriended with BitArray?

		operator unsigned();

		//Copied from termporary solution in _static, should be private
		BitArrayElemRefHelper& operator=(unsigned assignment);

	private:
		unsigned elementOffset;
		unsigned& refWord;
	};

	//Can be defined inside class definition
	BitArrayElemRefHelper::operator=(unsigned assignment)
	{
		//How to get the information about sizeOfElement and sizeOfArray?
		//Can this be get from the _dynamic instantiation of BitArray
	}
}

#endif //#ifndef BIT_ARRAY_ELEM_REF_HEPLER_DYNAMIC
