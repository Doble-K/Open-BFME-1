// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of the SpecialPowerTemplate destructor.

class AsciiString
{
public:
	~AsciiString();

private:
	char *m_text;
};

class AudioEventRTS
{
private:
	unsigned char m_data[0x6c];

public:
	virtual ~AudioEventRTS();
};

class Overridable
{
protected:
	__forceinline virtual ~Overridable()
	{
		if (m_nextOverride)
			m_nextOverride->deleteInstance();
		m_nextOverride = 0;
	}

	void deleteInstance()
	{
		delete this;
	}

	Overridable *m_nextOverride;
	bool m_isOverride;
};

class SpecialPowerTemplate : public Overridable
{
protected:
	virtual ~SpecialPowerTemplate();

private:
	AsciiString m_name;
	int m_id;
	int m_type;
	int m_reloadTime;
	int m_requiredScience;
	int m_academyClassificationType;
	AudioEventRTS m_initiateSound;
	AudioEventRTS m_initiateAtLocationSound;
	int m_detectionTime;
	int m_viewObjectDuration;
	float m_viewObjectRange;
	float m_radiusCursorRadius;
	bool m_publicTimer;
	bool m_sharedNSync;
	bool m_shortcutPower;
	AsciiString m_tail;
};

// ??1SpecialPowerTemplate@@MAE@XZ
SpecialPowerTemplate::~SpecialPowerTemplate()
{
}
