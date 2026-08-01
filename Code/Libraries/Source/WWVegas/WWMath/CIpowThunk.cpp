extern "C" __declspec(naked) void __CIpow()
{
    __asm {
        _emit 0FFh
        _emit 025h
        _emit 044h
        _emit 092h
        _emit 035h
        _emit 001h
    }
}
