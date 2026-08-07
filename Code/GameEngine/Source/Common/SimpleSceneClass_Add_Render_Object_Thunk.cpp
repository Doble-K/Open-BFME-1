// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift retail bytes to a standalone C++ thunk.
//
// Slot 2 of the SimpleSceneClass vtable, the twin of Remove_Render_Object at
// slot 3. It notifies the object through the virtual at +0x64 -- which is
// SceneClass::Add_Render_Object inlined, the 15-byte tail-call at 0x00942C10 --
// then adds it to the scene lists through GenericMultiListClass::Internal_Add
// and increments its reference count. Remove does the mirror of all three.

class RenderObjClass;
class SimpleSceneClass
{
public:
	virtual void Add_Render_Object(RenderObjClass *);
};

// ?Add_Render_Object@SimpleSceneClass@@UAEXPAVRenderObjClass@@@Z
__declspec(naked) void SimpleSceneClass::Add_Render_Object(RenderObjClass *)
{
	__asm {
		__emit 0x53
		__emit 0x56
		__emit 0x8b
		__emit 0x74
		__emit 0x24
		__emit 0x0c
		__emit 0x8b
		__emit 0x06
		__emit 0x57
		__emit 0x8b
		__emit 0xf9
		__emit 0x57
		__emit 0x8b
		__emit 0xce
		__emit 0xff
		__emit 0x50
		__emit 0x64
		__emit 0x6a
		__emit 0x01
		__emit 0x8d
		__emit 0x5e
		__emit 0x08
		__emit 0x53
		__emit 0x8d
		__emit 0x4f
		__emit 0x5c
		__emit 0xe8
		__emit 0xa1
		__emit 0x8f
		__emit 0x09
		__emit 0x00
		__emit 0x3c
		__emit 0x01
		__emit 0x75
		__emit 0x03
		__emit 0xff
		__emit 0x46
		__emit 0x04
		__emit 0x6a
		__emit 0x01
		__emit 0x53
		__emit 0x8d
		__emit 0x8f
		__emit 0xbc
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x8c
		__emit 0x8f
		__emit 0x09
		__emit 0x00
		__emit 0x8b
		__emit 0x16
		__emit 0x8b
		__emit 0xce
		__emit 0xff
		__emit 0x92
		__emit 0x9c
		__emit 0x01
		__emit 0x00
		__emit 0x00
		__emit 0x85
		__emit 0xc0
		__emit 0x74
		__emit 0x0e
		__emit 0x6a
		__emit 0x01
		__emit 0x53
		__emit 0x8d
		__emit 0x8f
		__emit 0xd4
		__emit 0x00
		__emit 0x00
		__emit 0x00
		__emit 0xe8
		__emit 0x70
		__emit 0x8f
		__emit 0x09
		__emit 0x00
		__emit 0x5f
		__emit 0x5e
		__emit 0x5b
		__emit 0xc2
		__emit 0x04
		__emit 0x00
	}
}
