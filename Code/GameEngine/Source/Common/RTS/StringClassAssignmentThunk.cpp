// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class StringClass
{
public:
    const StringClass &operator=(const StringClass &);
};

class StringClassAssignShim
{
public:
    const StringClass &assign(const StringClass &that);
};

const StringClass &StringClass::operator=(const StringClass &that)
{
    return ((StringClassAssignShim *)this)->assign(that);
}
