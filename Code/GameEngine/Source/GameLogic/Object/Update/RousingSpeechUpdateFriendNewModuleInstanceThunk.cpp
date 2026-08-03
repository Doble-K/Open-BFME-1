// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RousingSpeechUpdate::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class RousingSpeechUpdate
{
public:
	RousingSpeechUpdate(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0xfc];
};

// ?friend_newModuleInstance@RousingSpeechUpdate@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *RousingSpeechUpdate::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new RousingSpeechUpdate(thing, data);
}
