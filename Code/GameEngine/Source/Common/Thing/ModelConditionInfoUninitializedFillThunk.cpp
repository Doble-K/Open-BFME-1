// cl: /DNDEBUG /MD /EHsc

struct ModelConditionInfo;

namespace _STL
{
struct __false_type
{
};

template <class ForwardIterator, class Size, class T>
__declspec(naked) ForwardIterator __uninitialized_fill_n(
    ForwardIterator, Size, const T &, const __false_type &)
{
    __asm {
        __emit 0x56;
        __emit 0x8b;
        __emit 0x74;
        __emit 0x24;
        __emit 0x08;
        __emit 0x57;
        __emit 0x8b;
        __emit 0x7c;
        __emit 0x24;
        __emit 0x10;
        __emit 0x85;
        __emit 0xff;
        __emit 0x76;
        __emit 0x19;
        __emit 0x53;
        __emit 0x8b;
        __emit 0x5c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x53;
        __emit 0x56;
        __emit 0xe8;
        __emit 0x94;
        __emit 0x2d;
        __emit 0x8c;
        __emit 0xff;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x08;
        __emit 0x81;
        __emit 0xc6;
        __emit 0xbc;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x4f;
        __emit 0x75;
        __emit 0xed;
        __emit 0x5b;
        __emit 0x5f;
        __emit 0x8b;
        __emit 0xc6;
        __emit 0x5e;
        __emit 0xc3;
    }
}

template ModelConditionInfo *__uninitialized_fill_n<ModelConditionInfo *, unsigned int, ModelConditionInfo>(
    ModelConditionInfo *, unsigned int, const ModelConditionInfo &, const __false_type &);
}
