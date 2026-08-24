// ?getPerUnitSound@ThingTemplate@@QBEPBVAudioEventRTS@@ABVAsciiString@@@Z
// partial score=0.95 date=2026-08-25
// cl: /DNDEBUG /MD /EHs-c-

// Retail 0x00416FE0, 97 bytes. Two halves.
//
// The first walks a NULL-terminated array of pointers held at +0x158, asking
// each entry for something through vtable slot 11 and, when that answers,
// asking IT for the sound through vtable slot 1 with the name passed straight
// on. The first non-null sound wins. The loop's back edge is jne rather than
// jmp because the pointer increment already set the flags and the pointer is
// never zero.
//
// The second is the same override walk Rva2225E0Filter::accepts has at
// 0x003A04A0, MSVC unrolling one level of a recursive getFinalOverride: null
// yields null, otherwise the override's own +0x04 decides, and when it is
// clear the value left in eax is the override itself. The walked-to pointer
// then takes the name, and the last resort is the address of a fixed
// AudioEventRTS, which rides a DIR32 relocation from retail.

class AsciiString;
class AudioEventRTS;

class BfmeSoundLookup
{
public:
	virtual void bfmeLookupSlot00(void) = 0;
	virtual const AudioEventRTS *bfmeFind(const AsciiString &name) = 0;	// +0x04
};

class BfmeSoundProvider
{
public:
	virtual void bfmeSlot00(void) = 0;
	virtual void bfmeSlot04(void) = 0;
	virtual void bfmeSlot08(void) = 0;
	virtual void bfmeSlot0C(void) = 0;
	virtual void bfmeSlot10(void) = 0;
	virtual void bfmeSlot14(void) = 0;
	virtual void bfmeSlot18(void) = 0;
	virtual void bfmeSlot1C(void) = 0;
	virtual void bfmeSlot20(void) = 0;
	virtual void bfmeSlot24(void) = 0;
	virtual void bfmeSlot28(void) = 0;
	virtual BfmeSoundLookup *bfmeGetLookup(void) = 0;			// +0x2C
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride(void);				// ILT 0x000022BB
	const AudioEventRTS *bfmeLookupPerUnitSound(const AsciiString &name);	// ILT 0x0003B548

	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeNextOverride;					// +0x04
};

static BfmeOverridable *bfmeFinalOverride(BfmeOverridable *override)
{
	if (override == 0)
		return 0;

	if (override->m_bfmeNextOverride)
		return override->m_bfmeNextOverride->friend_getFinalOverride();

	return override;
}

extern const AudioEventRTS TheBfmeDefaultPerUnitSound;				// 0x012F1318

class ThingTemplate
{
public:
	const AudioEventRTS *getPerUnitSound(const AsciiString &name) const;

private:
	char m_bfmeHead[0x04];
	BfmeOverridable *m_bfmeOverride;					// +0x04
	char m_bfmeMid[0x158 - 0x08];
	BfmeSoundProvider **m_bfmeProviders;					// +0x158
};

// ?getPerUnitSound@ThingTemplate@@QBEPBVAudioEventRTS@@ABVAsciiString@@@Z
const AudioEventRTS *ThingTemplate::getPerUnitSound(const AsciiString &name) const
{
	BfmeSoundProvider **provider = m_bfmeProviders;

	if (provider)
	{
		do
		{
			BfmeSoundProvider *entry = *provider;

			if (entry == 0)
				break;

			BfmeSoundLookup *lookup = entry->bfmeGetLookup();

			if (lookup)
			{
				const AudioEventRTS *sound = lookup->bfmeFind(name);

				if (sound)
					return sound;
			}
		}
		while (++provider);
	}

	const AudioEventRTS *sound = bfmeFinalOverride(m_bfmeOverride)->bfmeLookupPerUnitSound(name);

	if (sound)
		return sound;

	return &TheBfmeDefaultPerUnitSound;
}
