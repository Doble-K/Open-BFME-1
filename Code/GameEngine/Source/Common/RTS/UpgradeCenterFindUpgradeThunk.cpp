// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /Code/GameEngine/Include/Precompiled /Code/Libraries/Source/WWVegas/WWLib

class AsciiString;
class UpgradeTemplate;

class UpgradeCenter
{
public:
    const UpgradeTemplate *findUpgrade(const AsciiString &) const;
};

class UpgradeCenterFindUpgradeShim
{
public:
    const UpgradeTemplate *find(const AsciiString &name) const;
};

const UpgradeTemplate *UpgradeCenter::findUpgrade(const AsciiString &name) const
{
    return ((const UpgradeCenterFindUpgradeShim *)this)->find(name);
}
