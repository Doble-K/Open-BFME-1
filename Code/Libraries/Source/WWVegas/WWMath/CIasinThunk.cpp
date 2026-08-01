extern "C" __declspec(naked) void __CIasin()
{
    __asm {
        _emit 0FFh
        _emit 025h
        _emit 034h
        _emit 092h
        _emit 035h
        _emit 001h
    }
}
