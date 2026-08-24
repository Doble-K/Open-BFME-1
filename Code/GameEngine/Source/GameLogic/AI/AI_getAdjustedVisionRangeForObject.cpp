// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AI::getAdjustedVisionRangeForObject, retail 0x0014A620, 125
// bytes, from the thunk queue -- the name sat on a five-byte thunk and this is
// the body it jumps to.
//
// The object's own vision range -- the body at 0x001C17C0 the ledger already
// carries -- comes first and is thrown away again when the object has no AI at
// +0x204. Otherwise the bonus at +0xBC is added, the AI's state word is read,
// and three of its values scale the result by one of two factors from +0x14 of
// the AI singleton, or flatten it to zero.
//
// The zero is loaded from memory rather than materialised, so it is an extern
// const and not a literal: written as 0.0f the compiler emits fldz.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

extern const Real BfmeZeroRange;				// 0x01075350

class BfmeObjectAI
{
public:
	UnsignedInt bfmeStateFlags(void);			// ILT 0x0001BB3F
};

class Object
{
public:
	Real getVisionRange(void) const;			// ILT 0x00014B4B

	char m_bfmeHeadA[0xBC];
	Real m_bfmeVisionBonus;					// +0x00BC
	char m_bfmeHeadB[0x204 - 0xC0];
	BfmeObjectAI *m_bfmeAI;					// +0x0204
};

class BfmeAIFactors
{
public:
	char m_bfmeHead[0x4C];
	Real m_bfme4C;						// +0x4C
	Real m_bfme50;						// +0x50
};

class BfmeAIRoot
{
public:
	char m_bfmeHead[0x14];
	BfmeAIFactors *m_bfmeFactors;				// +0x14
};

extern "C" BfmeAIRoot *TheAIParseDefinitionAI;			// 0x012EF214

class AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *object,
			Int flags);
};

// ?getAdjustedVisionRangeForObject@AI@@SAMPBVObject@@H@Z
Real AI::getAdjustedVisionRangeForObject(const Object *object, Int flags)
{
	Real range = object->getVisionRange();

	BfmeObjectAI *ai = object->m_bfmeAI;

	if (!ai)
		return BfmeZeroRange;

	range += object->m_bfmeVisionBonus;

	UnsignedInt state = ai->bfmeStateFlags();

	if ((flags & 2) && !(state & 1))
	{
		UnsignedInt kind = state & 0x1F00;

		// A switch, not a chain of ifs: the compares come out in case order
		// either way, but the switch is what puts the second arm's body after
		// the third one's.
		switch (kind)
		{
			case 0x100:
				return BfmeZeroRange;

			case 0x800:
				return range
					* TheAIParseDefinitionAI->m_bfmeFactors->m_bfme4C;

			case 0x1000:
				return range
					* TheAIParseDefinitionAI->m_bfmeFactors->m_bfme50;
		}
	}

	return range;
}
