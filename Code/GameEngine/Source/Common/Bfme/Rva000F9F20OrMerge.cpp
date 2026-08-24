// cl: /DNDEBUG /MD /EHsc

class Rva000F9F20
{
	unsigned first;
	unsigned second;
	unsigned third;
	unsigned fourth;
	unsigned fifth;
	unsigned sixth;

public:
	void merge( const Rva000F9F20 *other );
};

void Rva000F9F20::merge( const Rva000F9F20 *other )
{
	first |= other->first;
	second |= other->second;
	third |= other->third;
	fourth |= other->fourth;
	fifth |= other->fifth;
	sixth |= other->sixth;
}
