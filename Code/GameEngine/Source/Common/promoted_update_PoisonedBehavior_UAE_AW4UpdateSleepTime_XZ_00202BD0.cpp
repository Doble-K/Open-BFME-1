// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Grok promote from masm_dumps — retail 0x00202BD0 size 48
// was: Code/masm_dumps/update_PoisonedBehavior_00202BD0_packet301.asm

enum UpdateSleepTime { UPDATE_SLEEP_NONE=0 };
class PoisonedBehavior { public: virtual UpdateSleepTime update(void); };

// ?update@PoisonedBehavior@@UAE?AW4UpdateSleepTime@@XZ
__declspec(naked) UpdateSleepTime PoisonedBehavior::update(void)
{
__asm {
		_emit 08Bh
		_emit 041h
		_emit 018h
		_emit 083h
		_emit 0C1h
		_emit 0F0h
		_emit 085h
		_emit 0C0h
		_emit 074h
		_emit 020h
		_emit 08Bh
		_emit 015h
		_emit 098h
		_emit 008h
		_emit 02Fh
		_emit 001h
		_emit 03Bh
		_emit 042h
		_emit 03Ch
		_emit 074h
		_emit 015h
		_emit 068h
		_emit 0FFh
		_emit 0FFh
		_emit 0FFh
		_emit 03Fh
		_emit 068h
		_emit 0FFh
		_emit 0FFh
		_emit 0FFh
		_emit 03Fh
		_emit 050h
		_emit 08Bh
		_emit 041h
		_emit 024h
		_emit 050h
		_emit 0E8h
		_emit 0AEh
		_emit 0D6h
		_emit 0E1h
		_emit 0FFh
		_emit 0C3h
		_emit 0B8h
		_emit 0FFh
		_emit 0FFh
		_emit 0FFh
		_emit 03Fh
		_emit 0C3h
	}
}

