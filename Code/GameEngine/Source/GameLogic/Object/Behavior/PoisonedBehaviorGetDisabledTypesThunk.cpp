// cl: /DNDEBUG /MD /EHsc

// Standalone TU for PoisonedBehavior::getDisabledTypesToProcess.
// Retail: copy DISABLEDMASK_ALL into hidden return slot (ret 4).

template <int Bits>
class BitFlags
{
public:
	unsigned int m_bits;

	// Non-trivial copy forces MSVC 7.1 hidden return-pointer ABI.
	BitFlags(const BitFlags &other) : m_bits(other.m_bits) {}
};

// ?DISABLEDMASK_ALL@@3V?$BitFlags@$0N@@@A
extern BitFlags<13> DISABLEDMASK_ALL;

class PoisonedBehavior
{
public:
	virtual BitFlags<13> getDisabledTypesToProcess() const;
};

// ?getDisabledTypesToProcess@PoisonedBehavior@@UBE?AV?$BitFlags@$0N@@@XZ
BitFlags<13> PoisonedBehavior::getDisabledTypesToProcess() const
{
	return DISABLEDMASK_ALL;
}
