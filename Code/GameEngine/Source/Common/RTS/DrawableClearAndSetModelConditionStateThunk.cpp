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

class DrawableClearAndSetModelConditionStateShim
{
public:
    void run(ModelConditionFlagType clearFlags, ModelConditionFlagType setFlags);
};

void Drawable::clearAndSetModelConditionState(ModelConditionFlagType clearFlags, ModelConditionFlagType setFlags)
{
    ((DrawableClearAndSetModelConditionStateShim *)this)->run(clearFlags, setFlags);
}
