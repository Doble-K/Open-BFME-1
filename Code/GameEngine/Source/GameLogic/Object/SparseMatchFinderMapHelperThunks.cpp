class ArmorTemplateSet;
class WeaponTemplateSet;

template<int Bits>
class BitFlags
{
};

template<class Set, class Flags>
class SparseMatchFinder
{
public:
	class MapHelper
	{
	public:
		bool operator()(const Flags &, const Flags &) const;
	};
};

template<class Set, class Flags>
__declspec(naked) bool SparseMatchFinder<Set, Flags>::MapHelper::operator()(const Flags &, const Flags &) const
{
	__asm {
		_emit 0E9h
		_emit 099h
		_emit 05Dh
		_emit 013h
		_emit 000h
	}
}

template class SparseMatchFinder<ArmorTemplateSet, BitFlags<11> >;
