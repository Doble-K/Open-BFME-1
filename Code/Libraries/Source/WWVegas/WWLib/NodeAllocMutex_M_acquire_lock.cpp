// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ob0

namespace _STL
{
class NodeAllocMutex
{
public:
	void _M_acquire_lock();
};
}

void rva0082C760Acquire(_STL::NodeAllocMutex *);

void _STL::NodeAllocMutex::_M_acquire_lock()
{
	rva0082C760Acquire(this);
}
