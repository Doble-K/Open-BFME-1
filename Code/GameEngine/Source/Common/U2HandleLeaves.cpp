// Three unrelated-looking leaves that share one habit: each one turns a test
// into 0 / -1 or 0 / 1 with the carry flag rather than a branch.
//
// 0x00831F50 (16 bytes) -- a cdecl free function that calls the SECOND virtual
// (slot 4) on its only argument and returns that argument.  `this` is set from
// the argument, the vptr is read at offset 0, and eax is reloaded from the
// argument afterwards, so the return value is the object and not whatever the
// virtual returned.
//
// 0x008499F0 (18 bytes) -- a member that passes its +0x54 word to an imported
// function through the slot at 0x013593A8 and maps the result to 0 / -1 with
// `neg eax / sbb eax,eax`.  That pair is the compiler's `-(x != 0)`: a `bool`
// return would have been `setne al`, and a 0 / 1 int would have carried a
// second `neg`.  Nothing here names the import, so it is called by its slot.
//
// 0x00845250 (48 bytes) -- a cdecl comparison of two objects: each is given a
// chance to refresh itself (a member call guarded by its own +0 word being
// non-null), and then the two bytes at +6 are compared.  `sub / neg / sbb /
// inc` is `a == b` as a 0 / 1 int, which is why the result is an int and not a
// bool.  The refresh member is one function called on both objects, so both
// arguments have the same type.
//
// Identity is not recovered; every name is derived from an address.

struct Rva00831F50Object
{
	virtual void v0();
	virtual void release();
};

Rva00831F50Object *Rva00831F50Release(Rva00831F50Object *p)
{
	p->release();
	return p;
}

extern "C" __declspec(dllimport) int __cdecl u2_import_013593A8(void *handle);

struct Rva008499F0Owner
{
	char m_pad[0x54];
	void *m_handle;

	int isValid() const;
};

int Rva008499F0Owner::isValid() const
{
	return u2_import_013593A8(m_handle) != 0 ? -1 : 0;
}

struct Rva00845250Node
{
	void *m_source;
	char m_pad[2];
	char m_kind;

	void refresh();
};

int Rva00845250Equal(Rva00845250Node *a, Rva00845250Node *b)
{
	if (a->m_source != 0)
		a->refresh();
	if (b->m_source != 0)
		b->refresh();
	return a->m_kind == b->m_kind;
}

// 0x008442E0 (31 bytes) -- a four-argument member that forwards all four to a
// cdecl callee and returns its result: the arguments are re-pushed in reverse
// order with no adjustment, the callee's 0x10 of stack is cleaned by the
// caller, and the member itself pops 0x10 on return.  `this` is never read.
struct Rva008442E0Owner
{
	int forward(void *a, void *b, void *c, void *d) const;
};

extern int Rva00844230Do(void *a, void *b, void *c, void *d);

int Rva008442E0Owner::forward(void *a, void *b, void *c, void *d) const
{
	return Rva00844230Do(a, b, c, d);
}

// 0x00809500 (27 bytes) -- a lookup whose result is used only if it is
// non-null.  The lookup takes ONE argument and cleans it itself, so it is
// __stdcall and not the cdecl a plain free function would be; the second call
// takes the same argument but puts the lookup's result in ecx, so that one is a
// __thiscall member on the object just found.  The wrapper's own argument is
// passed on unchanged to both.
struct Rva00809500Entry
{
	char m_body[4];
};

struct Rva00809500Sink
{
	void accept(Rva00809500Entry *entry);
};

extern Rva00809500Sink *__stdcall Rva00809010Find(Rva00809500Entry *entry);

struct Rva00809500Owner
{
	void give(Rva00809500Entry *entry);
};

void Rva00809500Owner::give(Rva00809500Entry *entry)
{
	Rva00809500Sink *sink = Rva00809010Find(entry);
	if (sink != 0)
		sink->accept(entry);
}
