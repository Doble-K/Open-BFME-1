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

__declspec(naked) void ParticleSystemManager::destroyParticleSystemByID(ParticleSystemID)
{
    __asm {
        _emit 0E9h
        _emit 075h
        _emit 0E5h
        _emit 05Bh
        _emit 000h
    }
}
