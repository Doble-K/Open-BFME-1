// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AnimationSoundClientBehavior::friend_newModuleInstance factory.

class Module;
class Thing;
class ModuleData;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class AnimationSoundClientBehavior
{
public:
	AnimationSoundClientBehavior(Thing *, const ModuleData *);
	static Module *friend_newModuleInstance(Thing *, const ModuleData *);

private:
	unsigned char m_pad[0x1c];
};

// ?friend_newModuleInstance@AnimationSoundClientBehavior@@SAPAVModule@@PAVThing@@PBVModuleData@@@Z
Module *AnimationSoundClientBehavior::friend_newModuleInstance(Thing *thing, const ModuleData *data)
{
	return (Module *)new AnimationSoundClientBehavior(thing, data);
}
