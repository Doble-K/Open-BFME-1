// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Vector3;

template <class T>
class PrimitiveAnimationChannelClass
{
public:
    const PrimitiveAnimationChannelClass<T> &operator=(const PrimitiveAnimationChannelClass<T> &);
};

template <class T>
__declspec(naked) const PrimitiveAnimationChannelClass<T> &PrimitiveAnimationChannelClass<T>::operator=(const PrimitiveAnimationChannelClass<T> &)
{
    __asm {
        _emit 0E9h
        _emit 08Eh
        _emit 06Ah
        _emit 043h
        _emit 000h
    }
}

template const PrimitiveAnimationChannelClass<Vector3> &PrimitiveAnimationChannelClass<Vector3>::operator=(const PrimitiveAnimationChannelClass<Vector3> &);
