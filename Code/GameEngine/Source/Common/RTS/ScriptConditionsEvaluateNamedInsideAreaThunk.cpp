// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Parameter;

class ScriptConditions
{
protected:
    bool evaluateNamedInsideArea(Parameter *, Parameter *);
};

__declspec(naked) bool ScriptConditions::evaluateNamedInsideArea(Parameter *, Parameter *)
{
    __asm {
        _emit 0E9h
        _emit 02Ch
        _emit 0DEh
        _emit 031h
        _emit 000h
    }
}
