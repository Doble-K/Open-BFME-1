// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DBuffDraw::friend_newModuleInstance factory, retail 0x006BF7A0,
// converted out of a machine byte dump.
//
// Same three lines as every other module factory, so the code cannot name it.
// The draw-module registration block does: it builds the AsciiString "W3DBuffDraw"
// and pushes this factory's address as the argument beside it.
//
// Retail allocates 0x10 bytes, which is sizeof(W3DBuffDraw), and calls the
// constructor through link thunk 0x000144D9.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DBuffDraw
{
public:
	W3DBuffDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x10];
};

// ?friend_newModuleInstance@W3DBuffDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DBuffDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DBuffDraw(thing, data);
}
