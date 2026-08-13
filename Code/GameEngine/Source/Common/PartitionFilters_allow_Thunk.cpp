// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PartitionFilterIrregularArea::allow and PartitionFilterPlayer::allow.
//
// Both bodies are the Zero Hour source unchanged; what PartitionManager.cpp
// cannot reproduce is where the members sit. ZH's PartitionFilter contributes
// only a vtable pointer, so the first member of every filter lands at +0x04.
// Retail reads them from +0x08: BFME's base carries four more bytes ahead of
// the derived members. That shift is not this file's to fix -- correcting the
// base inside PartitionManager.cpp would move every one of its 74 matched rows
// -- so the filters are spelled locally with the gap made explicit, the same
// way PartitionFilterPlayerAffiliation_allow_Thunk.cpp already does.

struct Coord3D;
class Player;

bool PointInsideArea2D(const Coord3D *pt, const Coord3D *area, int numPoints);

class Object
{
public:
	// Thing::getPosition() is inlined at both call sites as &m_cachedPos;
	// retail reaches it with `add edx,0x38`.
	const Coord3D *getPosition(void) const
	{
		return (const Coord3D *)(m_unreconstructed_00 + 0x38);
	}

	Player *getControllingPlayer(void) const;			///< pinned at 0x00020824

private:
	unsigned char m_unreconstructed_00[0x38];
};

class PartitionFilterIrregularArea
{
protected:
	virtual bool allow(Object *);

private:
	unsigned char m_unreconstructed_04[0x08 - 4];		///< vtable slot then unpinned base bytes
	const Coord3D *m_area;								///< retail this+0x08
	int m_numPointsInArea;								///< retail this+0x0C
};

class PartitionFilterPlayer
{
protected:
	virtual bool allow(Object *);

private:
	unsigned char m_unreconstructed_04[0x08 - 4];		///< vtable slot then unpinned base bytes
	const Player *m_player;								///< retail this+0x08
	bool m_match;										///< retail this+0x0C
};

// ?allow@PartitionFilterIrregularArea@@MAE_NPAVObject@@@Z
bool PartitionFilterIrregularArea::allow(Object *other)
{

	return PointInsideArea2D(other->getPosition(), m_area, m_numPointsInArea);
}

// ?allow@PartitionFilterPlayer@@MAE_NPAVObject@@@Z
bool PartitionFilterPlayer::allow(Object *other)
{
	return ((m_player == other->getControllingPlayer()) == m_match);
}
