class ArmorTemplateSet;
class WeaponTemplateSet;

template <int Bits>
class BitFlags
{
};

template <class Set, class Flags>
class SparseMatchFinder
{
public:
	class MapHelper
	{
	public:
		bool operator()(const Flags &, const Flags &) const;
	};
};

class ArmorMapHelperShim
{
public:
	bool call(const BitFlags<11> &a, const BitFlags<11> &b) const;
};

class WeaponMapHelperShim
{
public:
	bool call(const BitFlags<17> &a, const BitFlags<17> &b) const;
};

template <class Set, class Flags>
bool SparseMatchFinder<Set, Flags>::MapHelper::operator()(const Flags &a, const Flags &b) const
{
	return ((ArmorMapHelperShim const *)this)->call((const BitFlags<11> &)a, (const BitFlags<11> &)b);
}

template class SparseMatchFinder<ArmorTemplateSet, BitFlags<11> >;

template <>
class SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >
{
public:
	class MapHelper
	{
	public:
		bool operator()(const BitFlags<17> &, const BitFlags<17> &) const;
	};
};

bool SparseMatchFinder<WeaponTemplateSet, BitFlags<17> >::MapHelper::operator()(const BitFlags<17> &a, const BitFlags<17> &b) const
{
	return ((WeaponMapHelperShim const *)this)->call(a, b);
}
