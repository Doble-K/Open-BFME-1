// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: VectorClass<MixFileCreator::FileInfoStruct>::Clear, retail 0x00934780.
//
// The Zero Hour body unchanged, and the VectorClass layout is ZH's too: the
// retail bytes read Vector at +0x04, IsAllocated at +0x0d and VectorMax at
// +0x08, which is exactly vptr / Vector / VectorMax / IsValid / IsAllocated.
//
// One byte disagrees, and it is the element size the vector destructor iterator
// is handed: retail pushes 0x74, mixfile.cpp compiles 0x10. FileInfoStruct is
// three unsigned longs and a StringClass, so
//
//     116 - 12 = 104 bytes of StringClass in BFME, against 4 here
//
// This tree's StringClass is one pointer. BFME's is not -- 0x68 bytes of it,
// which is the size of an embedded character buffer, not a handle. That is a
// tree-wide fact and correcting it belongs in wwstring.h, not here, so this TU
// spells the element as its retail size and leaves the class alone.
//
// The destructor pointer handed to ??_M confirms the element is non-trivially
// destructible, which a three-long POD would not be -- consistent with a
// StringClass member however it is laid out.

class MixFileCreator
{
public:
	struct FileInfoStruct {
		bool operator== (const FileInfoStruct &src)	{ return false; }
		bool operator!= (const FileInfoStruct &src)	{ return true; }

		~FileInfoStruct();							///< StringClass member makes this non-trivial

		unsigned long	CRC;
		unsigned long	Offset;
		unsigned long	Size;
		char			Filename[0x68];				///< StringClass; 104 bytes in BFME
	};
};

template<class T>
class VectorClass
{
public:
	virtual void Clear(void);

protected:
	T *Vector;										///< retail this+0x04
	int VectorMax;									///< retail this+0x08
	bool IsValid;									///< retail this+0x0c
	bool IsAllocated;								///< retail this+0x0d
};

// ?Clear@?$VectorClass@UFileInfoStruct@MixFileCreator@@@@UAEXXZ
template<class T>
void VectorClass<T>::Clear(void)
{
	if (Vector && IsAllocated) {
		delete[] Vector;
		Vector = 0;
	}
	IsAllocated = false;
	VectorMax = 0;
}

template class VectorClass<MixFileCreator::FileInfoStruct>;
