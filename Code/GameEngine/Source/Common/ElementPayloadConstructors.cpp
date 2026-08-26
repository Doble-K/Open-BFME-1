// These payload helpers are the direct callees of the element-stride walks.
// Their destination null checks explain why the wrappers may pass an empty
// slot, while the fixed first store distinguishes construction from copying.

extern int R2Data010EC764;

struct Elem32
{
	void * m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
	int m_at10;
	int m_at14;
	int m_at18;
	char m_at1C;
	char m_pad1D[ 3 ];
};

void gen003A84E0( Elem32 * slot, const Elem32 * source )
{
	if ( slot == 0 )
		return;

	slot->m_at00 = &R2Data010EC764;
	slot->m_at04 = source->m_at04;
	slot->m_at08 = source->m_at08;
	slot->m_at0C = source->m_at0C;
	slot->m_at10 = source->m_at10;
	slot->m_at14 = source->m_at14;
	slot->m_at18 = source->m_at18;
	slot->m_at1C = source->m_at1C;
}
