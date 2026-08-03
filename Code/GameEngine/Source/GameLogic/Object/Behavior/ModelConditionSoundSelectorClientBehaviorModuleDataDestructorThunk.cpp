// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ModelConditionSoundSelectorClientBehaviorModuleData dtor. PropagandaTower SEH pattern.

class ModelConditionSoundSelectorClientBehaviorModuleDataMember
{
public:
	~ModelConditionSoundSelectorClientBehaviorModuleDataMember();
};

class ModelConditionSoundSelectorClientBehaviorModuleDataBase
{
public:
	virtual ~ModelConditionSoundSelectorClientBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) ModelConditionSoundSelectorClientBehaviorModuleData : public ModelConditionSoundSelectorClientBehaviorModuleDataBase
{
public:
	virtual ~ModelConditionSoundSelectorClientBehaviorModuleData();
private:
	ModelConditionSoundSelectorClientBehaviorModuleDataMember m_member;
};

// ??1ModelConditionSoundSelectorClientBehaviorModuleData@@UAE@XZ
ModelConditionSoundSelectorClientBehaviorModuleData::~ModelConditionSoundSelectorClientBehaviorModuleData()
{
}
