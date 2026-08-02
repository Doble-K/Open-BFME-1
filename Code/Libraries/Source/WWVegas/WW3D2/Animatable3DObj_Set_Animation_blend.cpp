// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Animatable3DObjClass::Set_Animation blend overload — retail 0x009822C0 size 99
// Promoted from masm_dumps to Code/ naked C++ for bind spine.

class HAnimClass;
class Animatable3DObjClass {
public:
	virtual void Set_Animation(HAnimClass *motion0, float frame0, HAnimClass *motion1, float frame1, float percentage);
};

// ?Set_Animation@Animatable3DObjClass@@UAEXPAVHAnimClass@@M0MM@Z
__declspec(naked) void Animatable3DObjClass::Set_Animation(HAnimClass * /*motion0*/, float /*frame0*/, HAnimClass * /*motion1*/, float /*frame1*/, float /*percentage*/)
{
__asm {
		_emit 053h
		_emit 08Bh
		_emit 05Ch
		_emit 024h
		_emit 008h
		_emit 085h
		_emit 0DBh
		_emit 056h
		_emit 057h
		_emit 08Bh
		_emit 0F1h
		_emit 074h
		_emit 003h
		_emit 0FFh
		_emit 043h
		_emit 004h
		_emit 08Bh
		_emit 07Ch
		_emit 024h
		_emit 018h
		_emit 085h
		_emit 0FFh
		_emit 074h
		_emit 003h
		_emit 0FFh
		_emit 047h
		_emit 004h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 0AEh
		_emit 0FDh
		_emit 0FFh
		_emit 0FFh
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 014h
		_emit 08Bh
		_emit 04Ch
		_emit 024h
		_emit 01Ch
		_emit 08Bh
		_emit 054h
		_emit 024h
		_emit 020h
		_emit 089h
		_emit 0BEh
		_emit 00Ch
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 05Fh
		_emit 089h
		_emit 09Eh
		_emit 008h
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 0C7h
		_emit 086h
		_emit 004h
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 003h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 089h
		_emit 086h
		_emit 010h
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 089h
		_emit 08Eh
		_emit 014h
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 089h
		_emit 096h
		_emit 018h
		_emit 001h
		_emit 000h
		_emit 000h
		_emit 0C6h
		_emit 086h
		_emit 0F8h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 05Eh
		_emit 05Bh
		_emit 0C2h
		_emit 014h
		_emit 000h
	}
}

