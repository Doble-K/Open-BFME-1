// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class ModuleInfo
{
public:
	class Nugget
	{
	public:
		~Nugget();
	};
};

__declspec(naked) ModuleInfo::Nugget::~Nugget()
{
	__asm {
		_emit 06Ah
		_emit 0FFh
		_emit 068h
		_emit 0F8h
		_emit 0F4h
		_emit 004h
		_emit 001h
		_emit 064h
		_emit 0A1h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 050h
		_emit 064h
		_emit 089h
		_emit 025h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 051h
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 089h
		_emit 074h
		_emit 024h
		_emit 004h
		_emit 08Dh
		_emit 04Eh
		_emit 004h
		_emit 0C7h
		_emit 044h
		_emit 024h
		_emit 010h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0E8h
		_emit 0C5h
		_emit 068h
		_emit 08Bh
		_emit 0FFh
		_emit 08Bh
		_emit 0CEh
		_emit 0C7h
		_emit 044h
		_emit 024h
		_emit 010h
		_emit 0FFh
		_emit 0FFh
		_emit 0FFh
		_emit 0FFh
		_emit 0E8h
		_emit 044h
		_emit 077h
		_emit 011h
		_emit 000h
		_emit 08Bh
		_emit 04Ch
		_emit 024h
		_emit 008h
		_emit 05Eh
		_emit 064h
		_emit 089h
		_emit 00Dh
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 083h
		_emit 0C4h
		_emit 010h
		_emit 0C3h
	}
}

