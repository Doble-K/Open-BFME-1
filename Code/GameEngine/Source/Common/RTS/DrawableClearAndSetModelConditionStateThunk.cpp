// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /Code/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

enum ModelConditionFlagType
{
    ModelConditionFlagType_Thunk
};

class Drawable
{
public:
    void clearAndSetModelConditionState(ModelConditionFlagType, ModelConditionFlagType);
};

__declspec(naked) void Drawable::clearAndSetModelConditionState(ModelConditionFlagType, ModelConditionFlagType)
{
    __asm {
        _emit 0E9h
        _emit 089h
        _emit 09Dh
        _emit 050h
        _emit 000h
    }
}
