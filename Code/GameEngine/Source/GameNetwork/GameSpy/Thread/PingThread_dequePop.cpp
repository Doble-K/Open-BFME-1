// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4
#define _STLP_USE_STATIC_LIB
#include "PreRTS.h"
#include "GameNetwork/GameSpy/PingThread.h"

namespace std
{
	template <>
	__declspec(dllexport) void deque<PingResponse>::pop_front()
	{
		if (this->_M_start._M_cur != this->_M_start._M_last - 1) {
			_Destroy(this->_M_start._M_cur);
			++this->_M_start._M_cur;
		} else {
			_Destroy(this->_M_start._M_cur);
			if (this->_M_start._M_first != 0) {
				_Node_alloc::deallocate(this->_M_start._M_first,
				                        this->buffer_size() * sizeof(PingResponse));
			}
			this->_M_start._M_set_node(this->_M_start._M_node + 1);
			this->_M_start._M_cur = this->_M_start._M_first;
		}
	}
}
