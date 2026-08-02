// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Parameter;

class ScriptConditions
{
protected:
    bool evaluateNamedInsideArea(Parameter *, Parameter *);
};

class ScriptConditionsEvaluateNamedInsideAreaShim
{
public:
    bool evaluate(Parameter *a, Parameter *b);
};

bool ScriptConditions::evaluateNamedInsideArea(Parameter *a, Parameter *b)
{
    return ((ScriptConditionsEvaluateNamedInsideAreaShim *)this)->evaluate(a, b);
}
