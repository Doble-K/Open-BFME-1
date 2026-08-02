// Five-byte incremental-link thunks. Two rows in this file were removed because
// a 5-byte jmp row is unfalsifiable: every ILT entry in the image is
// E9 xx xx xx xx, so such a row byte-verifies against any of them and the name
// is never tested.
//
// Both removed rows named the wrong function, and following the thunk showed it.
// ControlBar::showBuildTooltipLayout claimed 0x00017503, whose body 0x000E7240
// is the matched ScienceStore::friend_lookupScience. ScriptEngine::undoNamedMapReveal
// claimed 0x0001019A, whose body 0x0034D320 is the matched
// ScriptEngine::removeNamedMapReveal.
//
// The one left is unrefuted rather than confirmed: its body at 0x0034D200 is
// unclaimed, so nothing contradicts it yet. Before adding a thunk row here,
// deref it and check what the body already belongs to.
class AsciiString
{
};

class ScriptEngine
{
public:
	void doNamedMapReveal(AsciiString const &);
};

class ScriptEnginedoNamedMapRevealShim
{
public:
	void doNamedMapReveal(AsciiString const & a0);
};

void ScriptEngine::doNamedMapReveal(AsciiString const & a0)
{
	((ScriptEnginedoNamedMapRevealShim *)this)->doNamedMapReveal(a0);
}


