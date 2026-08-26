// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// The body is gated by one virtual predicate and the Living World predicate,
// then walks the same 0x58-byte entry range used by the neighboring bodies.
// Flagged entries dispatch their own update; otherwise state 2 advances to 3
// once the simulation frame reaches the entry's frame.  Names remain
// descriptive because the owning subsystem is not proven.

class Rva00367810VirtualGate;

struct Rva00367810VirtualGateTable
{
	void *m_beforeTest[ 0x138 / sizeof( void * ) ];
	unsigned char (__fastcall *m_test)( Rva00367810VirtualGate *gate );
};

class Rva00367810VirtualGate
{
public:
	Rva00367810VirtualGateTable *m_table;
};

extern Rva00367810VirtualGate *Rva00367810TheVirtualGate;

class Rva00367810GameLogic
{
public:
	bool isLivingWorld();

	char         m_lead[ 0x3C ];
	unsigned int m_frame;
};

extern Rva00367810GameLogic *Rva00367810TheGameLogic;

class Rva00367810Entry
{
public:
	void update();

	char          m_lead[ 0x20 ];
	int           m_state;
	char          m_beforeFrame[ 4 ];
	unsigned int  m_frame;
	char          m_beforeFlag[ 0x20 ];
	unsigned char m_flag;
	char          m_tail[ 0x0B ];
};

class Rva00367810EntryRange
{
public:
	unsigned int size() const { return m_last - m_first; }
	Rva00367810Entry &operator[]( int index ) { return m_first[ index ]; }

private:
	Rva00367810Entry *m_first;
	Rva00367810Entry *m_last;
};

class Rva00367810Entries
{
public:
	void update();

private:
	char m_lead[ 0x18 ];
	Rva00367810EntryRange m_entries;
};

void Rva00367810Entries::update()
{
	Rva00367810VirtualGate *gate = Rva00367810TheVirtualGate;
	if( gate->m_table->m_test( gate ) )
		return;
	if( !Rva00367810TheGameLogic->isLivingWorld() )
		return;

	for( unsigned int index = 0; index < m_entries.size(); ++index )
	{
		Rva00367810Entry &entry = m_entries[ index ];
		if( entry.m_flag )
		{
			entry.update();
		}
		else if( entry.m_state == 2 &&
			Rva00367810TheGameLogic->m_frame >= entry.m_frame )
		{
			entry.m_state = 3;
		}
	}
}
