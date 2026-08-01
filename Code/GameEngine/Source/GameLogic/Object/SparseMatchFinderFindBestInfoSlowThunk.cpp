class WeaponTemplateSet
{
};

template <int Bits>
class BitFlags
{
};

namespace _STL
{
	template <class T>
	class allocator
	{
	};

	template <class T, class Allocator>
	class vector
	{
	};
}

template <class Set, class Flags>
class SparseMatchFinder
{
	const Set *findBestInfoSlow(_STL::vector<Set, _STL::allocator<Set> > const &, Flags const &) const;
};

template <class Set, class Flags>
__declspec(naked) const Set *SparseMatchFinder<Set, Flags>::findBestInfoSlow(_STL::vector<Set, _STL::allocator<Set> > const &, Flags const &) const
{
	__asm {
		_emit 0E9h
		_emit 031h
		_emit 005h
		_emit 013h
		_emit 000h
	}
}

template __declspec(naked) const WeaponTemplateSet *SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::findBestInfoSlow(_STL::vector<WeaponTemplateSet, _STL::allocator<WeaponTemplateSet> > const &, BitFlags<17> const &) const;
