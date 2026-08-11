// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
};

class ScriptConditionsInterface : public SubsystemInterface
{
public:
	virtual ~ScriptConditionsInterface() {}
};

class TransportStatus
{
public:
	virtual ~TransportStatus();
};

static TransportStatus *s_transportStatuses;

class ScriptConditions : public ScriptConditionsInterface
{
public:
	virtual ~ScriptConditions();
};

ScriptConditions::~ScriptConditions()
{
	delete s_transportStatuses;
	s_transportStatuses = 0;
}
