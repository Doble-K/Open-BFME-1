// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	AsciiString &operator =(const AsciiString &that);
};

class CommandButton
{
public:
	CommandButton();

	void setName(const AsciiString &name)
	{
		*reinterpret_cast<AsciiString *>(reinterpret_cast<char *>(this) + 0x0C) = name;
	}

	void friend_addToList(CommandButton **list)
	{
		*reinterpret_cast<CommandButton **>(reinterpret_cast<char *>(this) + 0x14) = *list;
		*list = this;
	}

private:
	unsigned char m_retailLayout[472];
};

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
	CommandButton *newCommandButton(const AsciiString & name);
	CommandSet *newCommandSet(const AsciiString & name);

private:
	unsigned char m_prefix[0x28];
	CommandButton *m_commandButtons;
	CommandSet *m_commandSets;
};

CommandButton *ControlBar::newCommandButton(const AsciiString &name)
{
	CommandButton *button = new CommandButton;
	button->setName(name);
	button->friend_addToList(&m_commandButtons);
	return button;
}

CommandSet *ControlBar::newCommandSet(const AsciiString & name)
{
	CommandSet *set = new CommandSet(name);
	set->friend_addToList(&m_commandSets);
	return set;
}
