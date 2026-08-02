// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

enum ParticleSystemID
{
    INVALID_PARTICLE_SYSTEM_ID = 0
};

class ParticleSystemManager
{
public:
    void destroyParticleSystemByID(ParticleSystemID id);
};

class ParticleSystemManagerDestroyByIDShim
{
public:
    void destroy(ParticleSystemID id);
};

void ParticleSystemManager::destroyParticleSystemByID(ParticleSystemID id)
{
    ((ParticleSystemManagerDestroyByIDShim *)this)->destroy(id);
}
