class W3DVolumetricShadowManager
{
public:
	bool ReAcquireResources();
};

__declspec(naked) bool W3DVolumetricShadowManager::ReAcquireResources()
{
	__asm {
		_emit 0E9h
		_emit 0C5h
		_emit 017h
		_emit 07Bh
		_emit 000h
	}
}
