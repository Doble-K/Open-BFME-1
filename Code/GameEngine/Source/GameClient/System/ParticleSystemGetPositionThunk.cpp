// cl: /DNDEBUG /MD /EHsc

struct Coord3D;

class ParticleSystem
{
public:
    void getPosition(Coord3D *);
};

__declspec(naked) void ParticleSystem::getPosition(Coord3D *)
{
    __asm {
        __emit 0x83;
        __emit 0xec;
        __emit 0x0c;
        __emit 0x8b;
        __emit 0x81;
        __emit 0xdc;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0xd9;
        __emit 0x81;
        __emit 0xcc;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x8b;
        __emit 0x89;
        __emit 0xec;
        __emit 0x00;
        __emit 0x00;
        __emit 0x00;
        __emit 0x89;
        __emit 0x44;
        __emit 0x24;
        __emit 0x04;
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x10;
        __emit 0x85;
        __emit 0xc0;
        __emit 0x89;
        __emit 0x4c;
        __emit 0x24;
        __emit 0x08;
        __emit 0x74;
        __emit 0x12;
        __emit 0x8b;
        __emit 0x54;
        __emit 0x24;
        __emit 0x04;
        __emit 0xd9;
        __emit 0x18;
        __emit 0x89;
        __emit 0x50;
        __emit 0x04;
        __emit 0x89;
        __emit 0x48;
        __emit 0x08;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x0c;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
        __emit 0xdd;
        __emit 0xd8;
        __emit 0x83;
        __emit 0xc4;
        __emit 0x0c;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}
