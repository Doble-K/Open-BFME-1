// cl: /DNDEBUG /MD /EHsc

class SupplyCenterDockUpdateModuleData
{
public:
    SupplyCenterDockUpdateModuleData();
};

__declspec(naked) SupplyCenterDockUpdateModuleData::SupplyCenterDockUpdateModuleData()
{
    __asm {
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 0E8h
        _emit 0A5h
        _emit 0CFh
        _emit 0D5h
        _emit 0FFh
        _emit 0B8h
        _emit 000h
        _emit 000h
        _emit 080h
        _emit 03Fh
        _emit 089h
        _emit 046h
        _emit 010h
        _emit 089h
        _emit 046h
        _emit 018h
        _emit 0C7h
        _emit 006h
        _emit 018h
        _emit 0B2h
        _emit 00Ch
        _emit 001h
        _emit 0C7h
        _emit 046h
        _emit 014h
        _emit 0FFh
        _emit 0FFh
        _emit 0FFh
        _emit 0FFh
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C3h
    }
}
