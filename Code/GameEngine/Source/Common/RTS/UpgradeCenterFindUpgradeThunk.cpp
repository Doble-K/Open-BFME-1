// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class AsciiString;
class UpgradeTemplate;

class UpgradeCenter
{
public:
    const UpgradeTemplate *findUpgrade(const AsciiString &) const;
};

__declspec(naked) const UpgradeTemplate *UpgradeCenter::findUpgrade(const AsciiString &) const
{
    __asm {
        _emit 0E9h
        _emit 081h
        _emit 0B7h
        _emit 00Dh
        _emit 000h
    }
}
