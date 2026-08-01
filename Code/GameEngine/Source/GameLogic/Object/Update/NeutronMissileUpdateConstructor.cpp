// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Thing
{
};

class ModuleData
{
};

class NeutronMissileUpdate
{
public:
	NeutronMissileUpdate( Thing *, const ModuleData * );
};

__declspec(naked) NeutronMissileUpdate::NeutronMissileUpdate( Thing *, const ModuleData * )
{
	__asm {
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 008h
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 08Bh
		_emit 04Ch
		_emit 024h
		_emit 008h
		_emit 050h
		_emit 051h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 061h
		_emit 0B4h
		_emit 0D7h
		_emit 0FFh
		_emit 033h
		_emit 0C0h
		_emit 088h
		_emit 086h
		_emit 089h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 089h
		_emit 086h
		_emit 08Ch
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C7h
		_emit 006h
		_emit 024h
		_emit 0ABh
		_emit 00Ch
		_emit 001h
		_emit 0C7h
		_emit 046h
		_emit 00Ch
		_emit 060h
		_emit 0AAh
		_emit 00Ch
		_emit 001h
		_emit 0C7h
		_emit 046h
		_emit 010h
		_emit 050h
		_emit 0AAh
		_emit 00Ch
		_emit 001h
		_emit 0C7h
		_emit 046h
		_emit 020h
		_emit 0F0h
		_emit 0A9h
		_emit 00Ch
		_emit 001h
		_emit 0C6h
		_emit 086h
		_emit 088h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 001h
		_emit 08Bh
		_emit 0C6h
		_emit 05Eh
		_emit 0C2h
		_emit 008h
		_emit 000h
	}
}

class MonsterDockUpdate
{
public:
	MonsterDockUpdate( Thing *, const ModuleData * );
};

__declspec(naked) MonsterDockUpdate::MonsterDockUpdate( Thing *, const ModuleData * )
{
	__asm {
		_emit 08Bh
		_emit 044h
		_emit 024h
		_emit 008h
		_emit 056h
		_emit 08Bh
		_emit 0F1h
		_emit 08Bh
		_emit 04Ch
		_emit 024h
		_emit 008h
		_emit 050h
		_emit 051h
		_emit 08Bh
		_emit 0CEh
		_emit 0E8h
		_emit 061h
		_emit 0B4h
		_emit 0D7h
		_emit 0FFh
		_emit 033h
		_emit 0C0h
		_emit 088h
		_emit 086h
		_emit 089h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 089h
		_emit 086h
		_emit 08Ch
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 0C7h
		_emit 006h
		_emit 024h
		_emit 0ABh
		_emit 00Ch
		_emit 001h
		_emit 0C7h
		_emit 046h
		_emit 00Ch
		_emit 060h
		_emit 0AAh
		_emit 00Ch
		_emit 001h
		_emit 0C7h
		_emit 046h
		_emit 010h
		_emit 050h
		_emit 0AAh
		_emit 00Ch
		_emit 001h
		_emit 0C7h
		_emit 046h
		_emit 020h
		_emit 0F0h
		_emit 0A9h
		_emit 00Ch
		_emit 001h
		_emit 0C6h
		_emit 086h
		_emit 088h
		_emit 000h
		_emit 000h
		_emit 000h
		_emit 001h
		_emit 08Bh
		_emit 0C6h
		_emit 05Eh
		_emit 0C2h
		_emit 008h
		_emit 000h
	}
}

