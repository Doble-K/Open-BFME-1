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

// Retail 0x0082AEC0 calls ~Rva0082AE60Exc.
class Rva0082AEC0Exc : public Rva0082AE60Exc
{
public:
  virtual ~Rva0082AEC0Exc();
};

Rva0082AEC0Exc::~Rva0082AEC0Exc()
{
}

// Retail 0x0082AEE0 calls ~Rva0082AE60Exc.
class Rva0082AEE0Exc : public Rva0082AE60Exc
{
public:
  virtual ~Rva0082AEE0Exc();
};

Rva0082AEE0Exc::~Rva0082AEE0Exc()
{
}

// Retail 0x0082AF00 calls ~Rva0082AE60Exc.
class Rva0082AF00Exc : public Rva0082AE60Exc
{
public:
  virtual ~Rva0082AF00Exc();
};

Rva0082AF00Exc::~Rva0082AF00Exc()
{
}

// Retail 0x0082AF20 calls ~Rva0082AE80Exc.
class Rva0082AF20Exc : public Rva0082AE80Exc
{
public:
  virtual ~Rva0082AF20Exc();
};

Rva0082AF20Exc::~Rva0082AF20Exc()
{
}

// Retail 0x0082AF40 calls ~Rva0082AE80Exc.
class Rva0082AF40Exc : public Rva0082AE80Exc
{
public:
  virtual ~Rva0082AF40Exc();
};

Rva0082AF40Exc::~Rva0082AF40Exc()
{
}

}
