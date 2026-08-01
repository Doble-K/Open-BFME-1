// cl: /DNDEBUG /MD /EHsc

class CivilianSpawnUpdateModuleData
{
public:
    CivilianSpawnUpdateModuleData();
};

__declspec(naked) CivilianSpawnUpdateModuleData::CivilianSpawnUpdateModuleData()
{
    __asm {
        _emit 6Ah
        _emit 0FFh
        _emit 68h
        _emit 78h
        _emit 12h
        _emit 01h
        _emit 01h
        _emit 64h
        _emit 0A1h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 50h
        _emit 64h
        _emit 89h
        _emit 25h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 51h
        _emit 56h
        _emit 8Bh
        _emit 0F1h
        _emit 57h
        _emit 89h
        _emit 74h
        _emit 24h
        _emit 08h
        _emit 33h
        _emit 0FFh
        _emit 8Dh
        _emit 4Eh
        _emit 0Ch
        _emit 89h
        _emit 7Ch
        _emit 24h
        _emit 14h
        _emit 0C7h
        _emit 06h
        _emit 48h
        _emit 0CEh
        _emit 0Bh
        _emit 01h
        _emit 0E8h
        _emit 0C8h
        _emit 0CFh
        _emit 0DAh
        _emit 0FFh
        _emit 8Bh
        _emit 4Ch
        _emit 24h
        _emit 0Ch
        _emit 89h
        _emit 7Eh
        _emit 14h
        _emit 89h
        _emit 7Eh
        _emit 18h
        _emit 89h
        _emit 7Eh
        _emit 1Ch
        _emit 0C7h
        _emit 46h
        _emit 08h
        _emit 05h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 0C7h
        _emit 46h
        _emit 10h
        _emit 2Ch
        _emit 01h
        _emit 00h
        _emit 00h
        _emit 5Fh
        _emit 8Bh
        _emit 0C6h
        _emit 5Eh
        _emit 64h
        _emit 89h
        _emit 0Dh
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 83h
        _emit 0C4h
        _emit 10h
        _emit 0C3h
    }
}
