// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib

class Upgrade;
class UpgradeTemplate;
enum UpgradeStatusType
{
    UpgradeStatusType_Thunk
};

class Player
{
public:
    Upgrade *addUpgrade(const UpgradeTemplate *, UpgradeStatusType);
};

class PlayerAddUpgradeShim
{
public:
    Upgrade *add(const UpgradeTemplate *tmpl, UpgradeStatusType status);
};

Upgrade *Player::addUpgrade(const UpgradeTemplate *tmpl, UpgradeStatusType status)
{
    return ((PlayerAddUpgradeShim *)this)->add(tmpl, status);
}
