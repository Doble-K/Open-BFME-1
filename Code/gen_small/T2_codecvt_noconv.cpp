// cl: /EHsc
// stlport
// A no-conversion character-conversion facet and two range hashes.  None of
// these rows contains a single relocation, so every byte is concrete.
//
// The three facet members are recognisable from their argument counts and the
// literal 3 they return, which is codecvt_base::noconv:
//   ret 0x10, four arguments, *arg4 = arg2       -- unshift(state, to, limit, next)
//   ret 0x1C, seven arguments, *arg4 = arg2 and *arg7 = arg5
//                                                -- out/in(state, from, end, next, to, limit, next)
//   ret 0x10, four arguments, min(arg4, arg3-arg2) selected THROUGH ADDRESSES
//                                                -- length(state, from, end, max)
// The address-selected minimum is what says the source called a min taking
// const references rather than writing the comparison out, so the vendored
// _STL::min is used rather than a ternary.
//
// Both widths are present: the byte facet and a second one whose members are
// byte-identical because the pointer arithmetic never appears in the body.
#include <algorithm>

typedef int T2MbState;

struct T2NoconvCodecvt
{
	int unshift(T2MbState *state, char *to, char *to_limit, char **to_next);
	int out(T2MbState *state, const char *from, const char *from_end,
	        const char **from_next, char *to, char *to_limit, char **to_next);
	int length(T2MbState *state, const char *from, const char *from_end, unsigned int max);
};

int T2NoconvCodecvt::unshift(T2MbState *, char *to, char *, char **to_next)
{
	*to_next = to;
	return 3;
}

int T2NoconvCodecvt::out(T2MbState *, const char *from, const char *,
                         const char **from_next, char *to, char *, char **to_next)
{
	*from_next = from;
	*to_next = to;
	return 3;
}

int T2NoconvCodecvt::length(T2MbState *, const char *from, const char *from_end,
                            unsigned int max)
{
	const unsigned int avail = (unsigned int)(from_end - from);
	return (int)(_STL::min)(avail, max);
}

struct T2NoconvCodecvtWide
{
	int unshift(T2MbState *state, char *to, char *to_limit, char **to_next);
	int out(T2MbState *state, const char *from, const char *from_end,
	        const char **from_next, char *to, char *to_limit, char **to_next);
	int length(T2MbState *state, const char *from, const char *from_end, unsigned int max);
};

int T2NoconvCodecvtWide::unshift(T2MbState *, char *to, char *, char **to_next)
{
	*to_next = to;
	return 3;
}

int T2NoconvCodecvtWide::out(T2MbState *, const char *from, const char *,
                             const char **from_next, char *to, char *, char **to_next)
{
	*from_next = from;
	*to_next = to;
	return 3;
}

int T2NoconvCodecvtWide::length(T2MbState *, const char *from, const char *from_end,
                                unsigned int max)
{
	const unsigned int avail = (unsigned int)(from_end - from);
	return (int)(_STL::min)(avail, max);
}

// h = h*5 + element, over a pointer range, callee-cleaned.
unsigned int __stdcall t2_hash_narrow_range(const char *first, const char *last)
{
	unsigned int h = 0;
	while (first < last)
	{
		h = h * 5 + *first;
		++first;
	}
	return h;
}

unsigned int __stdcall t2_hash_wide_range(const unsigned short *first,
                                          const unsigned short *last)
{
	unsigned int h = 0;
	while (first < last)
	{
		h = h * 5 + *first;
		++first;
	}
	return h;
}
