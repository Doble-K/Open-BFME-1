class INI;

class BoneFXUpdateModuleData
{
public:
	__declspec(dllexport) static void parseParticleSystem(INI *, void *, void *, const void *);
};

__declspec(naked) void BoneFXUpdateModuleData::parseParticleSystem(INI *, void *, void *, const void *)
{
	__asm {
		_emit 0E9h
		_emit 037h
		_emit 014h
		_emit 027h
		_emit 000h
	}
}

class TransitionDamageFXModuleData
{
public:
	__declspec(dllexport) static void parseParticleSystem(INI *, void *, void *, const void *);
};

__declspec(naked) void TransitionDamageFXModuleData::parseParticleSystem(INI *, void *, void *, const void *)
{
	__asm {
		_emit 0E9h
		_emit 0C8h
		_emit 013h
		_emit 023h
		_emit 000h
	}
}
