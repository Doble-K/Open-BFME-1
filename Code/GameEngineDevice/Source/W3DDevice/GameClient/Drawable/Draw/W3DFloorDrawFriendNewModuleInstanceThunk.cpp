// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DFloorDraw::friend_newModuleInstance factory, retail 0x006BF9C0,
// converted out of a machine byte dump.
//
// Same three lines as every other module factory, so the code cannot name it.
// The draw-module registration block does: it builds the AsciiString "W3DFloorDraw"
// and pushes this factory's address as the argument beside it.
//
// Retail allocates 0x14 bytes, which is sizeof(W3DFloorDraw), and calls the
// constructor through link thunk 0x0000A9D9.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DFloorDraw
{
public:
	W3DFloorDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x14];
};

// ?friend_newModuleInstance@W3DFloorDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DFloorDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DFloorDraw(thing, data);
}
