// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FILE: PlayerListUpdate.cpp ///////////////////////////////////////////////////
//
// PlayerList::update, split out of PlayerList.cpp because BFME's
// MAX_PLAYER_COUNT is 32 where the vendored ZH Common/GameCommon.h says 16.
//
// The retail body at 0x000DF2D0 is the ZH source verbatim -- compiled against
// the ZH header it reproduces all 32 bytes except one: retail loads the loop
// count as `mov edi,0x20`, the ZH constant gives `mov edi,0x10`.  Correcting
// the count inside PlayerList.cpp needs a TU-wide MAX_PLAYER_COUNT of 32, and
// that shifts the stack frames behind four already-matched EH funclets there
// (uw_00bfa5a3 under the constructor, uw_00bfa618/628/630 under newGame), so
// the count is corrected here instead, in a TU that owns this one body.
//
// The same count is what ??1PlayerList@@UAE@XZ was reconstructed from -- see
// `Player *m_players[32]` in
// Code/GameEngine/Source/Common/PlayerListDestructorThunk.cpp -- so two
// independent retail bodies agree on it.
//
// Identity: the loop's callee resolves through link thunk 0x0004771C to
// 0x000D9A80, which the ledger already carries as ?update@Player@@QAEXXZ.
// That is what separates this body from its two look-alikes.  PlayerList::update,
// ::newMap and ::updateTeamStates are the same code under three names and mask
// to identical bytes; only the callee tells them apart, and 0x000DF300 --
// byte-identical to this one outside the call site -- reaches a different
// 43-byte body at 0x000C9200 instead.
//
//-----------------------------------------------------------------------------

// Local spelling of just enough of the class graph to place m_players at +0x14:
// SubsystemInterface contributes a vptr and its AsciiString member (8 bytes),
// Snapshot a second vptr (4), then m_local and m_playerCount.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();

private:
	void *m_name;
};

class Snapshot
{
public:
	~Snapshot() {}
	virtual void crc() = 0;
	virtual void xfer() = 0;
	virtual void loadPostProcess() = 0;
};

class Player
{
public:
	void update();
};

class PlayerList : public SubsystemInterface, public Snapshot
{
public:
	virtual void update();

private:
	Player *m_local;
	int m_playerCount;
	Player *m_players[32];
};

//-----------------------------------------------------------------------------
// ?update@PlayerList@@UAEXXZ
void PlayerList::update()
{
	// update all players
	for( int i = 0; i < 32; i++ )
	{
		m_players[i]->update();
	}  // end for i

}
