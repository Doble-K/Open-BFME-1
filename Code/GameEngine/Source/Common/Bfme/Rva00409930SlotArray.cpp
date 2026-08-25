// 6-slot aggregate managing subobjects with position and flag updates

struct Block3
{
	unsigned int m_dword[3];
};

struct Rva00409930Target
{
	char          m_lead[0x44];
	unsigned char m_flag;
	char          m_pad[3];
	Block3        m_pos;

	void setPos( const Block3 &pos )
	{
		m_pos = pos;
	}
};

struct Rva00409930Slot
{
	char                m_lead1[0x14];
	int                 m_flag;
	char                m_lead2[0x8];
	Rva00409930Target  *m_target;
	char                m_trail[0x20];
};

class Rva00409930
{
public:
	void setTargetFlag( unsigned char value );
	void setPositions( const Block3 &pos );

	Rva00409930Slot m_slots[6];
};

void Rva00409930::setTargetFlag( unsigned char value )
{
	for ( int i = 0; i < 6; ++i )
	{
		if ( m_slots[i].m_flag == 1 && m_slots[i].m_target != 0 )
		{
			m_slots[i].m_target->m_flag = value;
		}
	}
}

void Rva00409930::setPositions( const Block3 &pos )
{
	for ( int i = 0; i < 6; ++i )
	{
		if ( m_slots[i].m_flag == 1 && m_slots[i].m_target != 0 )
		{
			m_slots[i].m_target->setPos( pos );
		}
	}
}
