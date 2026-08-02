// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Parameter;

class ScriptConditions
{
protected:
    bool evaluateTeamInsideAreaPartially(Parameter *, Parameter *, Parameter *);
};

class ScriptConditionsEvaluateTeamInsideAreaPartiallyShim
{
public:
    bool evaluate(Parameter *a, Parameter *b, Parameter *c);
};

bool ScriptConditions::evaluateTeamInsideAreaPartially(Parameter *a, Parameter *b, Parameter *c)
{
    return ((ScriptConditionsEvaluateTeamInsideAreaPartiallyShim *)this)->evaluate(a, b, c);
}
