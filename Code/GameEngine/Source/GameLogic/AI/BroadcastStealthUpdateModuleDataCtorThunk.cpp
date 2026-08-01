// cl: /DNDEBUG /MD /EHsc

class BroadcastStealthUpdateModuleData
{
public:
    BroadcastStealthUpdateModuleData();
};

__declspec(naked) BroadcastStealthUpdateModuleData::BroadcastStealthUpdateModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0C7h
        _emit 006h
        _emit 028h
        _emit 0F1h
        _emit 008h
        _emit 001h
        _emit 033h
        _emit 0C0h
        _emit 057h
        _emit 08Dh
        _emit 07Eh
        _emit 008h
        _emit 08Bh
        _emit 0CFh
        _emit 089h
        _emit 001h
        _emit 089h
        _emit 041h
        _emit 004h
        _emit 089h
        _emit 041h
        _emit 008h
        _emit 089h
        _emit 041h
        _emit 00Ch
        _emit 089h
        _emit 041h
        _emit 010h
        _emit 089h
        _emit 041h
        _emit 014h
        _emit 08Dh
        _emit 04Eh
        _emit 02Ch
        _emit 089h
        _emit 046h
        _emit 028h
        _emit 0E8h
        _emit 099h
        _emit 04Dh
        _emit 0EEh
        _emit 0FFh
        _emit 033h
        _emit 0D2h
        _emit 089h
        _emit 017h
        _emit 089h
        _emit 057h
        _emit 004h
        _emit 089h
        _emit 057h
        _emit 008h
        _emit 089h
        _emit 057h
        _emit 00Ch
        _emit 089h
        _emit 057h
        _emit 010h
        _emit 089h
        _emit 057h
        _emit 014h
        _emit 05Fh
        _emit 0C7h
        _emit 046h
        _emit 020h
        _emit 000h
        _emit 000h
        _emit 0C8h
        _emit 042h
        _emit 089h
        _emit 056h
        _emit 024h
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
