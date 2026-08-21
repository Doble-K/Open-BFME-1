// cl: -I Code/Libraries/Source/WWVegas/WWLib -I Code/Libraries/Source/WWVegas/WWMath -I Code/Libraries/Source/WWVegas/WWDebug -I Code/Libraries/Source/WWVegas/WWSaveLoad -I Code/Libraries/Include
//
// The two `Create_Z_Rotation_Matrix3` overloads from
// Code/Libraries/Source/WWVegas/WWMath/matrix3.h, emitted out of line.
//
// WHAT THE BYTES SHOW.  Both bodies take a hidden pointer in the first stack
// slot, write nine floats through it at +0x00..+0x20 and return with a plain
// `ret`: __cdecl returning a 36-byte class by value, i.e. a 3x3 matrix of
// Vector3 rows.  The nine values are, in order,
//
//     [0] = c   [1] = -s   [2] = 0
//     [3] = s   [4] = c    [5] = 0
//     [6] = 0   [7] = 0    [8] = 1
//
// which is a rotation about Z.  `Create_Z_Rotation_Matrix3(float s, float c)`
// in matrix3.h writes exactly those nine assignments in exactly that order into
// a local it then returns, and MSVC's named-return optimisation is what turns
// the local into the caller's buffer -- there is no copy in either body.
//
// THE SECOND OVERLOAD COMPUTES ITS OWN SINE AND COSINE: `fld` the angle,
// duplicate it, `fsin` one copy and `fcos` the other with an `fxch` between.
// That is `Create_Z_Rotation_Matrix3(sinf(rad), cosf(rad))` with the two-argument
// overload inlined into it, which is what matrix3.h's one-argument overload is.
// The ZERO STORES ARE HOISTED and the constant 1.0f is written last; that
// interleaving is the scheduler's, not the source's -- the source's own order
// survives in the float stores, which go down the x87 stack in the order the
// three rows are assigned.
//
// WHY THIS FILE EXISTS.  Both overloads are WWINLINE, which
// Code/Libraries/Source/WWVegas/WWLib/always.h defines as __forceinline, so no
// ordinary caller leaves a body behind -- yet retail has both out of line at
// 0x0060C460 and 0x0060C4B0.  Taking the address of a __forceinline function is
// what makes MSVC emit the standalone copy, so that is what the two helpers
// below do.  They are the scaffold, not the claim: neither exists in retail.

#include "matrix3.h"

typedef Matrix3 ( *U4ZRotFromSinCos )( float, float );
typedef Matrix3 ( *U4ZRotFromRadians )( float );

// ?u4ZRotFromSinCos@@YAP6A?AVMatrix3@@MM@ZXZ absent-from-retail
U4ZRotFromSinCos u4ZRotFromSinCos( void )
{
	return &Create_Z_Rotation_Matrix3;
}

// ?u4ZRotFromRadians@@YAP6A?AVMatrix3@@M@ZXZ absent-from-retail
U4ZRotFromRadians u4ZRotFromRadians( void )
{
	return &Create_Z_Rotation_Matrix3;
}
