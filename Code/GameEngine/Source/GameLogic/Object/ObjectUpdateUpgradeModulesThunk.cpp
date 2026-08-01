// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Object
{
public:
    void updateUpgradeModules();
};

__declspec(naked) void Object::updateUpgradeModules()
{
    __asm {
        _emit 0E9h
        _emit 02Ch
        _emit 0D8h
        _emit 019h
        _emit 000h
    }
}
