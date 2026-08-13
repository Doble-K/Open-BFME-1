// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift StreakLineClass::Delete_Point to clean C++.
//
// Same PointLocations container as Set_Widths (see
// StreakLineClass_Set_Widths_Thunk.cpp), but for Vector3 elements. That
// thunk already pins PointWidths at retail this+0xF4; compiling this member
// against the vendored streak.h layout put PointLocations 0x34 bytes too
// early (this+0xA0 instead of this+0xD4, confirmed against the disassembly's
// [ecx+0xE0] Count() field and [esi+... ] Vector/VectorMax/ActiveCount
// slots), so StreakLineClass carries 0x34 bytes of hidden/unreconstructed
// state ahead of PointLocations here, matching the same drift documented for
// PointWidths. Kept isolated as a local replica rather than touching the
// shared header, which other matched rows compile against.
//
// Delete_Point is just the Count() guard from streak.cpp, inlining straight
// into SimpleDynVecClass<Vector3>::Delete(index, true) from simplevec.h:
// memmove the tail down one slot, decrement ActiveCount, then Shrink()
// (`if (ActiveCount < VectorMax/4) Resize(ActiveCount)`) through vtable
// slot 1 (destructor is slot 0, Resize is slot 1).

#include <string.h>

struct StreakVector3
{
	float X, Y, Z;
};

class SimpleVecClass3
{
public:
	virtual ~SimpleVecClass3(void);					///< vtable +0x00
	virtual bool Resize(int newsize);					///< vtable +0x04
	virtual bool Uninitialised_Grow(int newsize);		///< vtable +0x08

	StreakVector3 &operator[](int index) { return Vector[index]; }

protected:
	StreakVector3 *Vector;								///< retail this+0x04
	int VectorMax;										///< retail this+0x08
};

class SimpleDynVecClass3 : public SimpleVecClass3
{
public:
	virtual ~SimpleDynVecClass3(void);
	virtual bool Resize(int newsize);

	int Count(void) const { return ActiveCount; }
	StreakVector3 &operator[](int index) { return Vector[index]; }

	bool Delete(int index, bool allow_shrink = true)
	{
		if (index < ActiveCount - 1)
		{
			memmove(&(*this)[index], &(*this)[index + 1], (ActiveCount - index - 1) * sizeof(StreakVector3));
		}
		ActiveCount--;

		if (allow_shrink)
		{
			Shrink();
		}

		return true;
	}

protected:
	bool Shrink(void)
	{
		// shrink the array if it is wasting more than 25%
		if (ActiveCount < VectorMax / 4)
		{
			return Resize(ActiveCount);
		}
		return true;
	}

	int ActiveCount;									///< retail this+0x0C
};

class StreakLineClass
{
public:
	void Delete_Point(unsigned int point_idx);

protected:
	unsigned char m_unreconstructed_00[0xD4];
	SimpleDynVecClass3 PointLocations;					///< retail this+0xD4
};

// ?Delete_Point@StreakLineClass@@QAEXI@Z
void StreakLineClass::Delete_Point(unsigned int point_idx)
{
	if (point_idx < (unsigned int)PointLocations.Count())
	{
		PointLocations.Delete(point_idx);
	}
}
