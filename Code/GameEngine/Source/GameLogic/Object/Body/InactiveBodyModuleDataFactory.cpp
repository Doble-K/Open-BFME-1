// cl: /DNDEBUG /MD /GX- /O2 /Ob2

struct FieldParse;

class INI
{
public:
	void initFromINI(void *object, const FieldParse *fields);
};

class ModuleData
{
public:
	ModuleData() {}
	virtual ~ModuleData();

private:
	int m_moduleTagNameKey;
};

class InactiveBody
{
public:
	static ModuleData *friend_newModuleData(INI *ini);
};

ModuleData *InactiveBody::friend_newModuleData(INI *ini)
{
	ModuleData *data = ::new ModuleData;
	if (ini)
		ini->initFromINI(data, 0);
	return data;
}
