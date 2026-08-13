// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialPowerTemplate::isShortcutPower, retail 0x00268920.
//
// A one-line accessor whose whole body is an inlined override walk, the same
// shape ?isSupplySourceSafe@AIPlayer@@QAE_NH@Z at 0x00166A10 turned out to
// carry. Overridable::friend_getFinalOverride is defined recursively and inline
// in the header, so MSVC unrolls two levels and leaves the rest to the
// out-of-line copy:
//
//   eax = this->m_nextOverride;  if null, answer is `this`
//   ecx = eax->m_nextOverride;   if null, answer is eax
//   otherwise call the out-of-line copy and take its result
//
// The two offsets that are this class's own: m_nextOverride at +0x04, so
// Overridable is a vtable pointer and that one member, and the flag at +0x115.
//
// The call goes to the NON-const overload -- retail's target resolves through
// ILT 0x00048C61 to 0x00097880, which the ledger carries as
// ?friend_getFinalOverride@Overridable@@QAEPAV1@XZ -- so the const walk is
// reached by casting rather than by a second const overload.

// MSVC does not expand a recursive inline at all unless inline_recursion is on;
// with it off the walk unrolls once and calls. Retail unrolls exactly twice, so
// the depth is pinned here rather than left to the default.
#pragma inline_recursion(on)
#pragma inline_depth(2)

class Overridable
{
public:
	virtual ~Overridable();

	Overridable *friend_getFinalOverride(void)
	{
		if (m_nextOverride)
			return m_nextOverride->friend_getFinalOverride();
		return this;
	}

protected:
	Overridable *m_nextOverride;					///< retail this+0x04
};

class SpecialPowerTemplate : public Overridable
{
public:
	bool isShortcutPower(void) const;

private:
	char m_unreconstructed_08[0x115 - 8];
	bool m_shortcutPower;							///< retail this+0x115
};

// ?isShortcutPower@SpecialPowerTemplate@@QBE_NXZ
bool SpecialPowerTemplate::isShortcutPower(void) const
{
	const SpecialPowerTemplate *self = (const SpecialPowerTemplate *)
		const_cast<SpecialPowerTemplate *>(this)->friend_getFinalOverride();
	return self->m_shortcutPower;
}
