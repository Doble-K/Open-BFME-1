// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Four retail bodies that are all one instantiation: STLport 4.5.3
// `list<T>::clear()`.  Retail, at 0x00129220:
//
//     mov  eax,[ebx]          ; the header node
//     mov  esi,[eax]          ; first = header->next
//     cmp  esi,eax            ; already empty?
//   loop:
//     mov  edi,esi
//     mov  esi,[esi]          ; advance BEFORE destroying
//     lea  ecx,[edi+8]        ; the value lives at node+8
//     call <element destructor>
//     push <node size> / push edi / call __node_alloc::_M_deallocate
//     cmp  esi,[ebx] ...      ; until back at the header
//     mov  [eax],eax          ; header->next = header
//     mov  [ebx+4],ebx        ; header->prev = header
//
// WHAT THE BYTES SHOW, and why this is one shape rather than four.  The walk
// advances `esi` to the successor BEFORE the value is destroyed, which is what
// distinguishes clear() from a destructor that could free the node first; the
// header is re-linked to point at itself rather than nulled, which is the
// circular-list invariant; and the deallocate size is a literal, so the node
// width is readable straight out of the push.  A list node is
// {next, prev, value} with the value at +8, so sizeof(T) is that literal minus
// eight -- 0x1C, 0x24, 0x3C and 0x14 for the four members here.
//
// TWO AXES, both read from the bytes: the node size, and the REL32 to the
// element destructor.  All four share one deallocate, `__node_alloc<...>::
// _M_deallocate` at 0x0082E5F0, which the ledger already names, so that callee
// needs no pin and the bytes prove it.
//
// IDENTITY IS NOT RECOVERED.  The payload types below are SYNTHETIC and
// deliberately anonymous: each reproduces a width and the fact that its
// destructor is a non-inline __thiscall taking nothing, never a class identity,
// and none of their names reaches the bytes.  The destructor each one is pinned
// to is read out of the retail REL32, so a wrong pin fails the gate loudly
// rather than matching anyway.

#include <list>

// A payload of exactly N bytes whose destructor is declared and never defined
// here: the call site is all the bytes carry, and the pin supplies its address.
// Instantiate ONLY clear(), not the whole class. `template class list<T>`
// instantiates every member, including remove(), which needs operator== on the
// payload -- a synthetic payload has none, and giving it one would put bytes in
// the image that retail does not have.
#define Z1_LIST_CLEAR( TAG, WIDTH )                                        \
    struct Z1Elem##TAG                                                     \
    {                                                                      \
        ~Z1Elem##TAG();                                                    \
        char m_pad[ WIDTH ];                                               \
    };                                                                     \
    template void _STL::_List_base< Z1Elem##TAG,                           \
                                    _STL::allocator< Z1Elem##TAG > >::clear();

Z1_LIST_CLEAR( 00129220, 0x1C )
Z1_LIST_CLEAR( 0013BF00, 0x24 )
Z1_LIST_CLEAR( 0056D960, 0x3C )
Z1_LIST_CLEAR( 0076AE50, 0x14 )
