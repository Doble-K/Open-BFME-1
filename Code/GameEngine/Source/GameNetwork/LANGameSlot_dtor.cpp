// cl: /DNDEBUG /MD /EHsc

// LANGameSlot::~LANGameSlot, 0x006858A0, 89 bytes.
//
// An empty body: everything in it is member and base destruction, in reverse
// declaration order, and each of the three calls is already ledgered or
// pinned. That is also what names it. The layout it destroys is exactly the
// one LANGameSlot_operator.cpp pins from the other side --
//
//   0x00  GameSlot base, 0x44 bytes, destroyed through ??1GameSlot@@QAE@XZ
//   0x44  LANPlayer m_user, destroyed through ??1LANPlayer@@QAE@XZ (0x00685830)
//   0x60  AsciiString m_serial, released in place
//   0x64  UnsignedInt m_lastHeard, trivial
//
// -- and it lands sizeof(LANGameSlot) on 0x68, which is the per-slot stride
// LANGameInfo's slot array already uses.
//
// GameSlot is modelled as an opaque 0x44-byte block rather than the
// polymorphic class it is. That is not cosmetic: with a vtable in the model
// MSVC opens the destructor with a six-byte vptr store that retail does not
// have, so the class this body destroys has no vtable of its own to reinstall.
// The base's fields are untouched here, so the block is all this file needs
// and it keeps the model out of LANGameSlot_operator.cpp, whose own matched
// operator= needs GameSlot's virtual to skip the vptr.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;

template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();				// ?releaseBuffer@?$StringBase@D@@AAEXXZ

	void *m_data;
};

class GameSlot
{
public:
	~GameSlot();					// ILT thunk 0x0000B988

	UnsignedByte m_bfmeBody[0x44];
};

class LANPlayer
{
public:
	~LANPlayer();					// ILT thunk 0x000240FF

	UnsignedByte m_bfmeBody[0x1C];
};

class LANGameSlot : public GameSlot
{
public:
	~LANGameSlot();

private:
	LANPlayer m_user;				// this+0x44
	StringBase<char> m_serial;			// this+0x60
	UnsignedInt m_lastHeard;			// this+0x64
};

// ??1LANGameSlot@@QAE@XZ
LANGameSlot::~LANGameSlot()
{
}
