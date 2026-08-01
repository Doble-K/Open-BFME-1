// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Parameter;

class ScriptConditions
{
protected:
    bool evaluateTeamInsideAreaPartially(Parameter *, Parameter *, Parameter *);
};

__declspec(naked) bool ScriptConditions::evaluateTeamInsideAreaPartially(Parameter *, Parameter *, Parameter *)
{
    __asm {
        _emit 0E9h
        _emit 08Bh
        _emit 09Dh
        _emit 02Dh
        _emit 000h
    }
}
