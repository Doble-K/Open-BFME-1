// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class AsciiString;
enum NameKeyType
{
    NameKeyType_Thunk
};
enum ModuleType
{
    ModuleType_Thunk
};

class ModuleFactory
{
protected:
    __declspec(dllexport) static NameKeyType makeDecoratedNameKey(const AsciiString &, ModuleType);
};

__declspec(naked) NameKeyType ModuleFactory::makeDecoratedNameKey(const AsciiString &, ModuleType)
{
    __asm {
        _emit 0E9h
        _emit 022h
        _emit 0AEh
        _emit 00Dh
        _emit 000h
    }
}
