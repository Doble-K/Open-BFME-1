class INI;

class BoneFXUpdateModuleData
{
public:
	static void parseParticleSystem(INI *, void *, void *, const void *);
};

class TransitionDamageFXModuleData
{
public:
	static void parseParticleSystem(INI *, void *, void *, const void *);
};

class BoneFXParseParticleSystemShim
{
public:
	static void parseParticleSystem(INI *, void *, void *, const void *);
};

class TransitionDamageFXParseParticleSystemShim
{
public:
	static void parseParticleSystem(INI *, void *, void *, const void *);
};

void BoneFXUpdateModuleData::parseParticleSystem(INI *a0, void *a1, void *a2, const void *a3)
{
	BoneFXParseParticleSystemShim::parseParticleSystem(a0, a1, a2, a3);
}

void TransitionDamageFXModuleData::parseParticleSystem(INI *a0, void *a1, void *a2, const void *a3)
{
	TransitionDamageFXParseParticleSystemShim::parseParticleSystem(a0, a1, a2, a3);
}
