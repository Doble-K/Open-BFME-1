class Object;

namespace _STL {

struct __true_type {};

template<class Type>
class allocator {};

template<class Type, class Allocator>
class vector {
protected:
    void _M_insert_overflow(Type*, Type const&, __true_type const&, unsigned int, bool);
};

__declspec(naked) void vector<Object*, allocator<Object*> >::_M_insert_overflow(
    Object**, Object* const&, __true_type const&, unsigned int, bool)
{
    __asm {
        _emit 0E9h
        _emit 04Fh
        _emit 0BAh
        _emit 070h
        _emit 000h
    }
}

}
