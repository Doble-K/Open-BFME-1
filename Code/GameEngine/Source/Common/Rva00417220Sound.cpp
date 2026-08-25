// cl: /O2 /Ob0

class AudioEventRTS;

class ThingTemplate
{
	const AudioEventRTS *bfmeLookupSound(int index) const;

public:
	int hasSound95() const;
};

int ThingTemplate::hasSound95() const
{
	return bfmeLookupSound(0x5F) != 0;
}
