// cl: /DNDEBUG /MD /EHsc

// W3DSupplyDrawModuleData's constructor, retail 0x0077DD50. The base's
// constructor, this class's own vftable pointer, and one field at +0x15C
// zeroed - which is what fixes the base's size.

class W3DSupplyDrawModuleDataBase
{
public:
	W3DSupplyDrawModuleDataBase();

	virtual void moduleDataAnchor();

private:
	unsigned char m_unmodelled_04[ 0x15C - 4 ];
};

class W3DSupplyDrawModuleData : public W3DSupplyDrawModuleDataBase
{
public:
	W3DSupplyDrawModuleData();

private:
	int m_unmodelled_15C;					// +0x15C
};

// ??0W3DSupplyDrawModuleData@@QAE@XZ
W3DSupplyDrawModuleData::W3DSupplyDrawModuleData()
	: m_unmodelled_15C( 0 )
{
}
