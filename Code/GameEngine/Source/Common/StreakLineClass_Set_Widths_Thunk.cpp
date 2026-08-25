// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the StreakLineClass::Set_Widths naked dump to clean C++.

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

class SimpleVecClass
{
public:
	virtual ~SimpleVecClass(void);
	virtual bool Resize(int newsize);
	virtual bool Uninitialised_Grow(int newsize);

	float &operator[](int index) { return Vector[index]; }
	int Length(void) const { return VectorMax; }

protected:
	float *Vector;
	int VectorMax;
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
			if (!Grow(new_size_hint))
				return false;
		}

		(*this)[ActiveCount++] = object;
		return true;
	}

	void Delete_All(bool allow_shrink = true)
	{
		ActiveCount = 0;
		if (allow_shrink)
			Shrink();
	}

protected:
	bool Grow(int new_size_hint)
	{
		int new_size = MAX(Length() + Length() / 4, Length() + 4);
		new_size = MAX(new_size, new_size_hint);
		return Resize(new_size);
	}

	bool Shrink(void)
	{
		if (ActiveCount < VectorMax / 4)
			return Resize(ActiveCount);
		return true;
	}

	int ActiveCount;
};

class StreakLineClass
{
protected:
	void Set_Widths(unsigned int num_points, float *widths);

	unsigned char m_unreconstructed_00[0xF4];
	SimpleDynVecClass PointWidths;
};

// Keep the STLPort inline helper symbols claimed by this focused TU while the
// real StreakLine method lives in WW3D2/streak.cpp.
void StreakLineClass::Set_Widths(unsigned int num_points, float *widths)
{
	if (num_points < 2 || !widths)
		return;

	PointWidths.Delete_All();
	for (unsigned int i = 0; i < num_points; i++)
		PointWidths.Add(widths[i], num_points);
}
