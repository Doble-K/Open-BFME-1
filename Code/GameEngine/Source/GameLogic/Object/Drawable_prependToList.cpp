// cl: /DNDEBUG /MD /EHsc

// Drawable::prependToList, retail 0x00411C50. No calls, four stores: clear this
// drawable's previous link at +0x108, point its next link at +0x104 at whatever
// the list head holds, back-link that one if there is one, then take the head.
//
// Retail loads the head twice rather than caching it - once for the next link
// and once for the back-link test - which is what reading *pListHead twice does
// through a pointer the compiler cannot prove is unaliased.

class Drawable
{
public:
	void prependToList( Drawable **pListHead );

private:
	unsigned char m_unmodelled_00[ 0x104 ];
	Drawable *m_nextDrawable;				// +0x104
	Drawable *m_prevDrawable;				// +0x108
};

// ?prependToList@Drawable@@QAEXPAPAV1@@Z
void Drawable::prependToList( Drawable **pListHead )
{
	m_prevDrawable = 0;
	m_nextDrawable = *pListHead;

	if( *pListHead )
		(*pListHead)->m_prevDrawable = this;

	*pListHead = this;
}
