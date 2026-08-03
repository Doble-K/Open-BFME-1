// cl: /DNDEBUG /MD /EHs-
// Open-BFME5: lift ScriptActions::doEnableOrDisableObjectDifficultyBonuses
// __emit thunk to clean C++. Retail iterates a linked list from a global
// manager (next pointer at +0x88), calls a per-element method with the bool,
// then stores the bool into a byte flag at global2+0x17634; the compiler
// sinks the flag store into both the loop-exit and empty-list paths.
// /EHs- because retail has no unwind frame.

class ScriptActionsDifficultyListManager;
class ScriptActions;

class ScriptActionsDifficultyListNode
{
public:
    void applyDifficultyBonuses(bool);

private:
    unsigned char m_pad[0x88];
    ScriptActionsDifficultyListNode *m_next;

    friend class ScriptActions;
};

class ScriptActionsDifficultyListManager
{
public:
    ScriptActionsDifficultyListNode *getDifficultyListHead();
};

class ScriptActionsDifficultyFlagHolder
{
public:
    unsigned char m_pad[0x17634];
    bool m_flag;
};

extern ScriptActionsDifficultyListManager *g_difficultyListManager;
extern ScriptActionsDifficultyFlagHolder *g_difficultyFlagHolder;

class ScriptActions
{
public:
    virtual void doEnableOrDisableObjectDifficultyBonuses(bool);
};

// ?doEnableOrDisableObjectDifficultyBonuses@ScriptActions@@UAEX_N@Z
void ScriptActions::doEnableOrDisableObjectDifficultyBonuses(bool enable)
{
    for (ScriptActionsDifficultyListNode *node = g_difficultyListManager->getDifficultyListHead();
         node;
         node = node->m_next)
    {
        node->applyDifficultyBonuses(enable);
    }
    g_difficultyFlagHolder->m_flag = enable;
}
