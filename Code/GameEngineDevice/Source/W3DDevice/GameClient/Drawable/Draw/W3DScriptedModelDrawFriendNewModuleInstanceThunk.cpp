// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DScriptedModelDraw::friend_newModuleInstance factory, retail 0x006BF040,
// converted out of a machine byte dump.
//
// Same three lines as every other module factory, so the code cannot name it.
// The draw-module registration block does: it builds the AsciiString "W3DScriptedModelDraw"
// and pushes this factory's address as the argument beside it.
//
// Retail allocates 0x27C bytes, which is sizeof(W3DScriptedModelDraw), and calls the
// constructor through link thunk 0x000285EC.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class W3DScriptedModelDraw
{
public:
	W3DScriptedModelDraw(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x27C];
};

// ?friend_newModuleInstance@W3DScriptedModelDraw@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *W3DScriptedModelDraw::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new W3DScriptedModelDraw(thing, data);
}
