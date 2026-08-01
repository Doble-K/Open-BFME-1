// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Object
{
public:
    void adjustModelConditionForWeaponStatus();
};

__declspec(naked) void Object::adjustModelConditionForWeaponStatus()
{
    __asm {
        _emit 0E9h
        _emit 018h
        _emit 02Ah
        _emit 01Ah
        _emit 000h
    }
}
