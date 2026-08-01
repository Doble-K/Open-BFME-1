// cl: /DNDEBUG /MD /EHsc

class TextureBaseClass
{
public:
    void Release_Ref();
};

__declspec(naked) void TextureBaseClass::Release_Ref()
{
    __asm {
        _emit 0F7h
        _emit 041h
        _emit 004h
        _emit 0FFh
        _emit 0FFh
        _emit 000h
        _emit 000h
        _emit 074h
        _emit 01Ah
        _emit 066h
        _emit 0FFh
        _emit 049h
        _emit 004h
        _emit 08Bh
        _emit 041h
        _emit 004h
        _emit 0A9h
        _emit 0FFh
        _emit 0FFh
        _emit 000h
        _emit 000h
        _emit 075h
        _emit 00Ch
        _emit 0A9h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 001h
        _emit 074h
        _emit 005h
        _emit 08Bh
        _emit 001h
        _emit 0FFh
        _emit 060h
        _emit 020h
        _emit 0C3h
    }
}
