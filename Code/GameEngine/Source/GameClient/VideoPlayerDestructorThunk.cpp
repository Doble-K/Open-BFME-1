// cl: /DNDEBUG /MD /EHsc

class __declspec(novtable) VideoPlayer
{
public:
    virtual ~VideoPlayer();
};

__declspec(naked) VideoPlayer::~VideoPlayer()
{
    __asm {
        _emit 0C7h
        _emit 001h
        _emit 0C0h
        _emit 0CCh
        _emit 012h
        _emit 001h
        _emit 03Bh
        _emit 00Dh
        _emit 090h
        _emit 0B1h
        _emit 030h
        _emit 001h
        _emit 075h
        _emit 00Ah
        _emit 0C7h
        _emit 005h
        _emit 090h
        _emit 0B1h
        _emit 030h
        _emit 001h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 000h
        _emit 0C7h
        _emit 001h
        _emit 060h
        _emit 0CCh
        _emit 012h
        _emit 001h
        _emit 0E9h
        _emit 08Dh
        _emit 054h
        _emit 018h
        _emit 000h
    }
}
