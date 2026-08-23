// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: _Rb_tree<GameSpyStagingRoom *, GameSortStruct>::_M_insert, retail
// 0x0053F7E0, 191 bytes. The name was parked on a 5-byte thunk.
//
// STLport's own body out of the real header. The element is a pointer, so the
// value goes into the node with a plain store rather than the out-of-line
// _Construct the class-typed trees need, and the comparison is a call on the
// tree's own comparator subobject at this+8.
#define _STLP_NO_EXCEPTIONS 1
#include <set>

class GameSpyStagingRoom;

struct GameSortStruct
{
	bool operator()(GameSpyStagingRoom *left, GameSpyStagingRoom *right) const;
};

typedef _STL::set<GameSpyStagingRoom *, GameSortStruct> BfmeStagingRoomSet;

void BfmeStagingRoomSetAnchor(BfmeStagingRoomSet &rooms, GameSpyStagingRoom *room)
{
	rooms.insert(room);
}
