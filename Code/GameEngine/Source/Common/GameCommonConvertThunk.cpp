// cl: /DNDEBUG /MD /EHsc
// Open-BFME1: siblings of INI::parseVelocityReal / parseAccelerationReal /
// parseAngularVelocityReal's frame-rate conversion helpers.
//
// Zero Hour declares these as `inline` in Common/GameCommon.h, right after
// ConvertDurationFromMsecsToFrames (already matched at retail 0x000B94B0,
// Code/GameEngine/Source/GameLogic/Object/Weapon.cpp). Because the compiler
// here does not fold `inline` calls away, each TU that calls one of these
// gets its own out-of-line COMDAT body, and the three bodies land immediately
// after ConvertDurationFromMsecsToFrames at 0x000B94C0/0x000B94D0/0x000B94F0
// -- an 11/17/17-byte run of near-identical fld/fmul/fmul/ret shapes that
// differ only in which float constant(s) they multiply by.
//
// BFME1 runs game logic at 5 frames/sec (not Zero Hour's 30): the retail
// bytes at 0x000B94B0 multiply by 0.005 (5/1000 = LOGICFRAMES_PER_MSEC_REAL)
// and the bodies below multiply by 0.2 (1/5 = SECONDS_PER_LOGICFRAME_REAL)
// alone, by 0.2 twice (SEC_PER_LOGICFRAME_SQR = 0.2*0.2), and by 0.2 then
// 0.017453292f (PI/180 = RADS_PER_DEGREE) -- exactly the three sibling
// formulas in GameCommon.h, confirming both the constant and the family.
//
// SECONDS_PER_LOGICFRAME_REAL and RADS_PER_DEGREE are `extern const Real`
// globals in the real header (their float payload lives in one defining TU,
// at these retail data addresses); every OTHER translation unit that reads
// them sees only an opaque memory operand, so the compiler cannot constant
// -fold SECONDS_PER_LOGICFRAME_REAL*SECONDS_PER_LOGICFRAME_REAL down to a
// single 0.04f literal the way it would for a same-TU local `const` -- which
// is exactly why the retail bytes still show two separate loads of the same
// address. Referencing them the same way (a known global at its retail
// absolute address) reproduces that.
typedef float Real;

#define SECONDS_PER_LOGICFRAME_REAL (*reinterpret_cast<const Real *>(0x012A86A8))
#define RADS_PER_DEGREE (*reinterpret_cast<const Real *>(0x01082C40))
Real ConvertVelocityInSecsToFrames(Real distPerMsec)
{
	return (SECONDS_PER_LOGICFRAME_REAL * distPerMsec);
}

// retail loads SECONDS_PER_LOGICFRAME_REAL's address twice rather than
// reusing the FPU-stack copy (fld st(0)) the optimizer prefers; /Op
// (improve floating-point consistency) turns off that FP-load reuse without
// disabling straight-line codegen, reproducing the two direct loads.
Real ConvertAccelerationInSecsToFrames(Real distPerSec2)
{
	const Real SEC_PER_LOGICFRAME_SQR = (SECONDS_PER_LOGICFRAME_REAL * SECONDS_PER_LOGICFRAME_REAL);
	return (distPerSec2 * SEC_PER_LOGICFRAME_SQR);
}

Real ConvertAngularVelocityInDegreesPerSecToRadsPerFrame(Real degPerSec)
{
	return (degPerSec * (SECONDS_PER_LOGICFRAME_REAL * RADS_PER_DEGREE));
}
