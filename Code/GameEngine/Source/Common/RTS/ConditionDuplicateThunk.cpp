// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class Condition
{
public:
    Condition *duplicate() const;
};

__declspec(naked) Condition *Condition::duplicate() const
{
    __asm {
        _emit 0E9h
        _emit 0A2h
        _emit 0BBh
        _emit 033h
        _emit 000h
    }
}
