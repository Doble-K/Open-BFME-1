// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

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
        _emit 0ECh
        _emit 06Fh
        _emit 008h
        _emit 000h
    }
}

template const PrimitiveAnimationChannelClass<float> &PrimitiveAnimationChannelClass<float>::operator=(const PrimitiveAnimationChannelClass<float> &);
