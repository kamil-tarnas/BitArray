#ifndef BIT_ARRAY_ELEM_REF_HEPLER_DYNAMIC
#define BIT_ARRAY_ELEM_REF_HEPLER_DYNAMIC

namespace dynamic
{
	// Does this need to be a template? What would be the use cases of template instances?
	class BitArrayElemRefHelper
	{
		//TODO: What could be declared as private?
	public:
		// Constructors? Befriended with BitArray?

		operator unsigned();
		BitArrayElemRefHelper& operator=(unsigned assignment);

	private:
		unsigned elementOffset;
		unsigned& refWord;
	};
}

#endif //#ifndef BIT_ARRAY_ELEM_REF_HEPLER_DYNAMIC
