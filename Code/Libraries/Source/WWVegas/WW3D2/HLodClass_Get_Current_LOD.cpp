// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// HLodClass::Get_Current_LOD — retail 0x00978F20 size 47
// Promoted from masm_dumps to Code/ naked C++ (Grok conversion).

class RenderObjClass;
class HLodClass {
public:
	virtual RenderObjClass *Get_Current_LOD(void);
};

// ?Get_Current_LOD@HLodClass@@UAEPAVRenderObjClass@@XZ
__declspec(naked) RenderObjClass *HLodClass::Get_Current_LOD(void)
{
__asm {
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 08Bh
		_emit 08Eh
		_emit 028h
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 08Bh
		_emit 006h
		_emit 051h
		_emit 08Bh
		_emit 0CEh
		_emit 0FFh
		_emit 090h
		_emit 028h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 085h
		_emit 0C0h
		_emit 075h
		_emit 002h
		_emit 05Eh
		_emit 0C3h
		_emit 08Bh
		_emit 086h
		_emit 028h
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 08Bh
		_emit 016h
		_emit 06Ah
		_emit 000h
		_emit 050h
		_emit 08Bh
		_emit 0CEh
		_emit 0FFh
		_emit 092h
		_emit 030h
		_emit 002h
		_emit 000h
		_emit 000h
		_emit 05Eh
		_emit 0C3h
	}
}

