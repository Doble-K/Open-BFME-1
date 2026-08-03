// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: AudioManager::addAudioEvent
// Retail 19B: push defaults (1,1,0) then event; thiscall impl; ret 4.

class AudioEventRTS;

class AudioManager
{
public:
	virtual unsigned int addAudioEvent(const AudioEventRTS *event);
	unsigned int addAudioEventEx(const AudioEventRTS *event, int a, int b, int c);
};

// ?addAudioEvent@AudioManager@@UAEIPBVAudioEventRTS@@@Z
unsigned int AudioManager::addAudioEvent(const AudioEventRTS *event)
{
	return addAudioEventEx(event, 0, 1, 1);
}
