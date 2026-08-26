#include <string.h>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class Rva00369860Pair
{
public:
	int m_first;
	int m_second;
};

class Rva00369860Range
{
public:
	__forceinline void clear(void) { erase(m_begin, m_end); }

private:
	__forceinline Rva00369860Pair *erase(Rva00369860Pair *first, Rva00369860Pair *last)
	{
		int count = m_end - last;
		Rva00369860Pair *output = first;
		while( count > 0 )
		{
			*output = *last;
			++last;
			++output;
			--count;
		}
		m_end = output;
		return first;
	}

	Rva00369860Pair *m_begin;
	Rva00369860Pair *m_end;
	Rva00369860Pair *m_capacity;
};

class Rva00369860State
{
public:
	Rva00369860Range m_pairs;
	char m_unreconstructed0C[ 8 ];
	int m_mode;
	int m_field18;
	int m_firstValues[ 10 ];
	int m_secondValues[ 10 ];
	int m_field6C;
	int m_field70;
	int m_field74;
	int m_field78;
	int m_field7C;
	int m_field80;
	char m_unreconstructed84[ 8 ];
	bool m_flag8C;

	void reset(int mode);
};

void Rva00369860State::reset(int mode)
{
	m_mode = mode;
	m_field18 = 0;
	m_pairs.clear();
	memset(m_firstValues, 0, sizeof(m_firstValues));
	memset(m_secondValues, 0, sizeof(m_secondValues));
	m_flag8C = false;
	// Keep the flag store ahead of the saved-register restore, as in retail.
	_ReadWriteBarrier();
	m_field6C = 0;
	m_field78 = 0;
	m_field70 = 0;
	m_field7C = 0;
	m_field74 = 0;
	m_field80 = 0;
}

// @?reset@Rva00369860State@@QAEXH@Z 0x00369860
