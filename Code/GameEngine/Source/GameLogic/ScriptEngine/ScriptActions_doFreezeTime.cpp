// cl: /DNDEBUG /MD /EHsc

class ScriptActions
{
protected:
    void doFreezeTime(void);
};

__declspec(naked) void ScriptActions::doFreezeTime(void)
{
    __asm {
        _emit 08Bh
        _emit 00Dh
        _emit 06Ch
        _emit 007h
        _emit 02Fh
        _emit 001h
        _emit 0E9h
        _emit 021h
        _emit 007h
        _emit 0D3h
        _emit 0FFh
    }
}
