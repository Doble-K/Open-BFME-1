// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DHordeModelDraw::friend_newModuleInstance factory, retail 0x006BFBE0,
// converted out of a machine byte dump.
//
// Same three lines as every other module factory, so the code cannot name it.
// The draw-module registration block does: it builds the AsciiString "W3DHordeModelDraw"
// and pushes this factory's address as the argument beside it.
//
// Retail allocates 0x288 bytes, which is sizeof(W3DHordeModelDraw), and calls the
// constructor through link thunk 0x00008378.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DHordeModelDraw
{
public:
	W3DHordeModelDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x288];
};

// ?friend_newModuleInstance@W3DHordeModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DHordeModelDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DHordeModelDraw(thing, data);
}
