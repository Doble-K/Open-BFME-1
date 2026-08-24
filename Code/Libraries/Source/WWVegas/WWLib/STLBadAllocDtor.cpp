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

// Retail 0x0082AE60 stores its vptr then calls ~bad_alloc. Identity of the
// derived type is not yet recovered; the shape is the derived destructor.
class Rva0082AE60Exc : public bad_alloc
{
public:
  virtual ~Rva0082AE60Exc();
};

Rva0082AE60Exc::~Rva0082AE60Exc()
{
}

// Retail 0x0082AE80: sibling of Rva0082AE60Exc, also calls ~bad_alloc.
class Rva0082AE80Exc : public bad_alloc
{
public:
  virtual ~Rva0082AE80Exc();
};

Rva0082AE80Exc::~Rva0082AE80Exc()
{
}

// Retail 0x0082AEA0 calls ~Rva0082AE60Exc.
class Rva0082AEA0Exc : public Rva0082AE60Exc
{
public:
  virtual ~Rva0082AEA0Exc();
};

Rva0082AEA0Exc::~Rva0082AEA0Exc()
{
}

}
