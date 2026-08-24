// cl: /DNDEBUG /MD /Od

// Retail 0x0082AE40 is STLport/MSVC
//   _STL::bad_alloc::~bad_alloc()
// (??1bad_alloc@_STL@@UAE@XZ).
// Stores this-class vptr, then calls dllimport std::exception::~exception.
// /Od keeps this in [ebp-4]; no /EHsc so the base-dtor call has no EH frame.

#include <exception>

namespace _STL {

class bad_alloc : public std::exception
{
public:
  virtual ~bad_alloc();
};

bad_alloc::~bad_alloc()
{
}

}
