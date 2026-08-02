// cl: /DNDEBUG /MD /EHsc

class PlayerTemplate;

namespace _STL
{
struct __false_type
{
};

template <class In, class Out>
__declspec(naked) Out __uninitialized_copy(In, In, Out, const __false_type &)
{
    __asm {
        __emit 0x53;
        __emit 0x8b;
        __emit 0x5c;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x56;
        __emit 0x8b;
        __emit 0x74;
        __emit 0x24;
        __emit 0x0c;
        __emit 0x3b;
        __emit 0xf3;
        __emit 0x57;
        __emit 0x8b;
        __emit 0x7c;
        __emit 0x24;
        __emit 0x18;
        __emit 0x74;
        __emit 0x1a;
        __emit 0x56;
        __emit 0x57;
        __emit 0xe8;
        __emit 0x36;
        __emit 0x07;
        __emit 0xf4;
        __emit 0xff;
        __emit 0x81;
        __emit 0xc6;
        __emit 0x24;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x08;
        __emit 0x81;
        __emit 0xc7;
        __emit 0x24;
        __emit 0x01;
        __emit 0x00;
        __emit 0x00;
        __emit 0x3b;
        __emit 0xf3;
        __emit 0x75;
        __emit 0xe6;
        __emit 0x8b;
        __emit 0xc7;
        __emit 0x5f;
        __emit 0x5e;
        __emit 0x5b;
        __emit 0xc3;
    }
}

template PlayerTemplate *__uninitialized_copy<PlayerTemplate *, PlayerTemplate *>(
    PlayerTemplate *, PlayerTemplate *, PlayerTemplate *, const __false_type &);
}
