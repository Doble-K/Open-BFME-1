// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep

class AutoFindHealingUpdateModuleData
{
	virtual void virtualAnchor( void ) = 0;
	unsigned int m_padding;
	unsigned int m_first;
	unsigned int m_second;
	float m_searchDelay;
	float m_searchRange;

public:
	AutoFindHealingUpdateModuleData( void );
};

AutoFindHealingUpdateModuleData::AutoFindHealingUpdateModuleData( void )
{
	m_first = 0;
	m_second = 0;
	m_searchDelay = 0.95f;
	m_searchRange = 0.25f;
}
