// cl: /DNDEBUG /MD /EHsc

class PSResponse;

namespace _STL
{
template <class T, class U>
void _Construct(T *, const U &);

template <class T, class U>
__declspec(naked) void _Construct(T *, const U &)
{
    __asm {
        __emit 0x6a;
        __emit 0xff;
        __emit 0x68;
        __emit 0x11;
        __emit 0xa3;
        __emit 0x01;
        __emit 0x01;
        __emit 0x64;
        __emit 0xa1;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x50;
        __emit 0x64;
        __emit 0x89;
        __emit 0x25;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x51;
        __emit 0x56;
        __emit 0x8b;
        __emit 0x74;
        __emit 0x24;
        __emit 0x18;
        __emit 0x89;
        __emit 0x74;
        __emit 0x24;
        __emit 0x04;
        __emit 0x85;
        __emit 0xf6;
        __emit 0xc7;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x74;
        __emit 0x22;
        __emit 0x57;
        __emit 0x8b;
        __emit 0x7c;
        __emit 0x24;
        __emit 0x20;
        __emit 0x8b;
        __emit 0x07;
        __emit 0x8d;
        __emit 0x4f;
        __emit 0x04;
        __emit 0x51;
        __emit 0x8d;
        __emit 0x4e;
        __emit 0x04;
        __emit 0x89;
        __emit 0x06;
        __emit 0xe8;
        __emit 0x60;
        __emit 0xf5;
        __emit 0x51;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x57;
        __emit 0x08;
        __emit 0x89;
        __emit 0x56;
        __emit 0x08;
        __emit 0x8b;
        __emit 0x47;
        __emit 0x0c;
        __emit 0x89;
        __emit 0x46;
        __emit 0x0c;
        __emit 0x5f;
        __emit 0x8b;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x08;
        __emit 0x5e;
        __emit 0x64;
        __emit 0x89;
        __emit 0x0d;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x10;
        __emit 0xc3;
    }
}

template __declspec(naked) void _Construct<PSResponse, PSResponse>(PSResponse *, const PSResponse &);
}
