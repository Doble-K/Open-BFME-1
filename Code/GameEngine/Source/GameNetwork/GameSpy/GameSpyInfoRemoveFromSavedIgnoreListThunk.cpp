// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef int Int;
typedef bool Bool;

class AsciiString
{
public:
	static const AsciiString TheEmptyString;
};

namespace _STL
{
template <class First, class Second> struct pair;
template <class Type> struct _Select1st;
template <class Type> struct less;
template <class Type> class allocator;

template <class Key, class Value, class Select, class Less, class Allocator>
class _Rb_tree
{
public:
	unsigned int erase(const Key &key);
};
}

struct Gen_t_006342a0_p12cd
{
	int data[3];
};

typedef _STL::pair<const int, Gen_t_006342a0_p12cd> SavedIgnorePair;
typedef _STL::_Rb_tree<
	int,
	SavedIgnorePair,
	_STL::_Select1st<SavedIgnorePair>,
	_STL::less<int>,
	_STL::allocator<SavedIgnorePair> > SavedIgnoreMap;

class UserPreferences
{
public:
	virtual Bool write(void);

private:
	unsigned char m_map[12];
	AsciiString m_filename;
};

class IgnorePreferences : public UserPreferences
{
public:
	IgnorePreferences();
	virtual ~IgnorePreferences();
	void setIgnore(const AsciiString &userName, Int profileID, Bool ignore);
};

class GameSpyInfo
{
public:
	virtual void removeFromSavedIgnoreList(Int profileID);

private:
	unsigned char m_pad[0x6d0];
	SavedIgnoreMap m_savedIgnoreMap;
};

// ?removeFromSavedIgnoreList@GameSpyInfo@@UAEXH@Z
void GameSpyInfo::removeFromSavedIgnoreList(Int profileID)
{
	m_savedIgnoreMap.erase(profileID);
	IgnorePreferences pref;
	pref.setIgnore(AsciiString::TheEmptyString, profileID, false);
	pref.write();
}
