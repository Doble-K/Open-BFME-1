// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the StreakLineClass::Set_Widths naked dump to clean C++.
//
// Zero Hour's streak.cpp body. PointWidths is a SimpleDynVecClass<float>, not a
// DynamicVectorClass, and that matters: the whole function is the container's
// inline machinery with only Resize left as an out-of-line virtual, so the
// members have to be spelled the way simplevec.h spells them or nothing lines
// up.
//
// The three arithmetic shapes in the dump are all from that header:
//   * Delete_All -> ActiveCount = 0 then Shrink, which is
//     `if (ActiveCount < VectorMax/4) Resize(ActiveCount)`. With ActiveCount
//     just set to zero the compare folds to `VectorMax/4 > 0` and the call
//     becomes Resize(0) -- that is the leading divide-by-four, not a growth
//     step.
//   * Grow -> MAX(Length() + Length()/4, Length() + 4) then MAX against the
//     caller's hint, which is the second divide-by-four and the two
//     compare-and-move pairs.
//   * Add -> the `ActiveCount >= VectorMax` guard and the trailing
//     `(*this)[ActiveCount++] = object`.
//
// Resize is vtable slot 1: the base declares the destructor first, then Resize,
// then Uninitialised_Grow, and both call sites here go through [vtable+4].
//
// The WWASSERT(0) in the reject path is a no-op under NDEBUG, so the guard is
// just the short-circuited `num_points < 2 || !widths`. MSVC shrink-wraps the
// register saves around it, which is why ebp and edi are pushed only after the
// first test passes.
//
// Retail pins the layout: PointWidths sits at this+0xF4, with Vector at +0x04,
// VectorMax at +0x08 and ActiveCount at +0x0C of it.

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

class SimpleVecClass
{
public:
	virtual ~SimpleVecClass(void);						///< vtable +0x00
	virtual bool Resize(int newsize);					///< vtable +0x04
	virtual bool Uninitialised_Grow(int newsize);		///< vtable +0x08

	float &operator[](int index) { return Vector[index]; }
	int Length(void) const { return VectorMax; }

protected:
	float *Vector;										///< retail this+0x04
	int VectorMax;										///< retail this+0x08
};

class SimpleDynVecClass : public SimpleVecClass
{
public:
	virtual ~SimpleDynVecClass(void);
	virtual bool Resize(int newsize);

	float &operator[](int index) { return Vector[index]; }

	bool Add(float const &object, int new_size_hint = 0)
	{
		if (ActiveCount >= VectorMax)
		{
			// We are out of space so tell the vector to grow
			if (!Grow(new_size_hint))
			{
				return false;
			}
		}

		(*this)[ActiveCount++] = object;
		return true;
	}

	void Delete_All(bool allow_shrink = true)
	{
		ActiveCount = 0;

		if (allow_shrink)
		{
			Shrink();
		}
	}

protected:
	bool Grow(int new_size_hint)
	{
		// grow to 25% bigger, at least 4 elements, at least up to the hint
		int new_size = MAX(Length() + Length() / 4, Length() + 4);
		new_size = MAX(new_size, new_size_hint);

		return Resize(new_size);
	}

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
protected:
	void Set_Widths(unsigned int num_points, float *widths);

	unsigned char m_unreconstructed_00[0xF4];
	SimpleDynVecClass PointWidths;						///< retail this+0xF4
};

// ?Set_Widths@StreakLineClass@@IAEXIPAM@Z
void StreakLineClass::Set_Widths(unsigned int num_points, float *widths)
{
	if (num_points < 2 || !widths)
	{
		// WWASSERT(0) -- compiled out under NDEBUG
		return;
	}

	PointWidths.Delete_All();
	for (unsigned int i = 0; i < num_points; i++)
	{
		PointWidths.Add(widths[i], num_points);
	}
}
