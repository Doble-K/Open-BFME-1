// cl: /DNDEBUG /MD /EHsc

class InstantDeathBehaviorModuleData
{
public:
    __declspec(noinline) virtual ~InstantDeathBehaviorModuleData();
};

// The scalar destructor's retail body remains ledger-backed by its MASM dump;
// this definition emits the compiler-owned deleting destructor at the vtable
// slot.
InstantDeathBehaviorModuleData::~InstantDeathBehaviorModuleData()
{
}
