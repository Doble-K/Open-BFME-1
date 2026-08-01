// cl: /DNDEBUG /MD /EHsc

class ObjectCreationUpgradeModuleData
{
public:
    ObjectCreationUpgradeModuleData();
};

__declspec(naked) ObjectCreationUpgradeModuleData::ObjectCreationUpgradeModuleData()
{
    __asm {
        _emit 53h
        _emit 56h
        _emit 8Bh
        _emit 0F1h
        _emit 33h
        _emit 0DBh
        _emit 8Dh
        _emit 4Eh
        _emit 10h
        _emit 0C7h
        _emit 06h
        _emit 80h
        _emit 0D7h
        _emit 0Ch
        _emit 01h
        _emit 89h
        _emit 5Eh
        _emit 08h
        _emit 89h
        _emit 5Eh
        _emit 0Ch
        _emit 0E8h
        _emit 0DCh
        _emit 7Ah
        _emit 0D3h
        _emit 0FFh
        _emit 89h
        _emit 5Eh
        _emit 78h
        _emit 89h
        _emit 5Eh
        _emit 7Ch
        _emit 89h
        _emit 9Eh
        _emit 80h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 9Eh
        _emit 84h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 9Eh
        _emit 88h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 9Eh
        _emit 8Ch
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 88h
        _emit 9Eh
        _emit 90h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 9Eh
        _emit 0A0h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 9Eh
        _emit 98h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 89h
        _emit 9Eh
        _emit 9Ch
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 0C7h
        _emit 86h
        _emit 94h
        _emit 00h
        _emit 00h
        _emit 00h
        _emit 0FFh
        _emit 0FFh
        _emit 0FFh
        _emit 0FFh
        _emit 8Bh
        _emit 0C6h
        _emit 5Eh
        _emit 5Bh
        _emit 0C3h
    }
}
