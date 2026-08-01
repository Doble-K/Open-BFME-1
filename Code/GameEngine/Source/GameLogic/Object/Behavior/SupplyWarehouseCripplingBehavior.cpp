// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep

class SupplyWarehouseCripplingBehaviorModuleData
{
	virtual void virtualAnchor( void ) = 0;
	unsigned int m_padding;
	unsigned int m_first;
	unsigned int m_second;
	unsigned int m_third;

public:
	SupplyWarehouseCripplingBehaviorModuleData( void );
};

SupplyWarehouseCripplingBehaviorModuleData::SupplyWarehouseCripplingBehaviorModuleData( void )
{
	m_first = 0;
	m_second = 0;
	m_third = 0;
}
