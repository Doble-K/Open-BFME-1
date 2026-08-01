// cl: /DNDEBUG /MD /EHsc

class LadderPref
{
};

namespace _STL
{
template <class First, class Second>
class pair
{
public:
    pair(const First &, const Second &);
};

template <class First, class Second>
__declspec(naked) pair<First, Second>::pair(const First &, const Second &)
{
    __asm {
        _emit 08Bh
        _emit 044h
        _emit 024h
        _emit 004h
        _emit 08Bh
        _emit 054h
        _emit 024h
        _emit 008h
        _emit 056h
        _emit 08Bh
        _emit 0F1h
        _emit 08Bh
        _emit 008h
        _emit 089h
        _emit 00Eh
        _emit 052h
        _emit 08Dh
        _emit 04Eh
        _emit 004h
        _emit 0E8h
        _emit 0C1h
        _emit 0E5h
        _emit 0F9h
        _emit 0FFh
        _emit 08Bh
        _emit 0C6h
        _emit 05Eh
        _emit 0C2h
        _emit 008h
        _emit 000h
    }
}
}

template class _STL::pair<const long, LadderPref>;
