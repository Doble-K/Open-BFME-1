// cl: /DNDEBUG /MD /EHsc
// Open-BFME: DisconnectManager::isPlayerVotedOut, retail 0x0066BC30, 70 bytes.
//
// The reference's body with two BFME changes. untranslatedSlotPosition is
// inlined and only half of it survives -- the slot is known not to be -1 by
// then, so all that is left is the `if (slot >= localSlot) ++slot` -- and the
// threshold is no longer `conMgr->getNumPlayers() - 1` but a helper of the
// manager's own, taking the same translated slot and connection manager the
// vote count does.
//
// That helper has no reference twin and nothing here names it beyond what it
// returns, so it carries a descriptive name. countVotesForPlayer takes the
// connection manager here too, where the ledger's existing pin has it taking
// the slot alone.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class ConnectionManager
{
public:
	Int getLocalPlayerID(void);				// ILT 0x0004A291
};

class DisconnectManager
{
protected:
	Bool isPlayerVotedOut(Int slot, ConnectionManager *conMgr);

	Int untranslatedSlotPosition(Int slot, Int localSlot)
	{
		if (slot == -1) {
			return localSlot;
		}

		if (slot < localSlot) {
			return slot;
		}

		return (slot + 1);
	}

	Int countVotesForPlayer(Int slot, ConnectionManager *conMgr);	// ILT 0x00003751
	Int getVotesNeededToKick(Int slot, ConnectionManager *conMgr);	// ILT 0x0002FA63
};

Bool DisconnectManager::isPlayerVotedOut(Int slot, ConnectionManager *conMgr) {
	if (slot == -1) {
		// we can't vote out ourselves.
		return false;
	}
	Int transSlot = untranslatedSlotPosition(slot, conMgr->getLocalPlayerID());
	Int numVotes = countVotesForPlayer(transSlot, conMgr);
	if (numVotes >= getVotesNeededToKick(transSlot, conMgr)) {
		return true;
	}
	return false;
}
