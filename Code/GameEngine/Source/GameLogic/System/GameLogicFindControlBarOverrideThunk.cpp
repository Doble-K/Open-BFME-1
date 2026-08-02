class AsciiString
{
};

class CommandButton
{
};

class GameLogic
{
public:
    bool findControlBarOverride(const AsciiString &, int, const CommandButton *&) const;
};

class GameLogicFindControlBarOverrideShim
{
public:
    bool find(const AsciiString &name, int slot, const CommandButton *&out) const;
};

bool GameLogic::findControlBarOverride(const AsciiString &name, int slot, const CommandButton *&out) const
{
    return ((const GameLogicFindControlBarOverrideShim *)this)->find(name, slot, out);
}
