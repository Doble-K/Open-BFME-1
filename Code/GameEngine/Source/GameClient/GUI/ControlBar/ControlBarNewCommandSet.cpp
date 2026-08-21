// cl: /DNDEBUG /MD /EHsc

class AsciiString;

class CommandSet
{
public:
	CommandSet(const AsciiString & name);
	void friend_addToList(CommandSet **list);

private:
	unsigned char m_retailLayout[100];
};

class ControlBar
{
protected:
	CommandSet *newCommandSet(const AsciiString & name);

private:
	unsigned char m_prefix[0x2C];
	CommandSet *m_commandSets;
};

CommandSet *ControlBar::newCommandSet(const AsciiString & name)
{
	CommandSet *set = new CommandSet(name);
	set->friend_addToList(&m_commandSets);
	return set;
}
