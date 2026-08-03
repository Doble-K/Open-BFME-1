// cl: /DNDEBUG /MD /EHsc

template <int Bits>
class BitFlags
{
};

class PoisonedBehavior
{
public:
    virtual BitFlags<13> getDisabledTypesToProcess() const;
};

// ?getDisabledTypesToProcess@PoisonedBehavior@@UBE?AV?$BitFlags@$0N@@@XZ
__declspec(naked) BitFlags<13> PoisonedBehavior::getDisabledTypesToProcess() const
{
    __asm {
        __emit 0x8b;
        __emit 0x44;
        __emit 0x24;
        __emit 0x04;
        __emit 0x8b;
        __emit 0x0d;
        __emit 0x5c;
        __emit 0xd8;
        __emit 0x2e;
        __emit 0x01;
        __emit 0x89;
        __emit 0x08;
        __emit 0xc2;
        __emit 0x04;
        __emit 0x00;
    }
}
