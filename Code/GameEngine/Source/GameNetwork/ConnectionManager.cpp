// cl: /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/connectionmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

#include "GameLogic/GameLogic.h"
#include "GameNetwork/NetCommandMsg.h"
#include "GameNetwork/ConnectionManager.h"

template class std::map<UnsignedShort, UnsignedByte>;

void ConnectionManager::processProgress(NetProgressCommandMsg *msg)
{
	TheGameLogic->processProgress(msg->getPlayerID(), msg->getPercentage());
}

// ?getLocalPlayerID@ConnectionManager@@QAEIXZ
UnsignedInt ConnectionManager::getLocalPlayerID()
{
	return m_localSlot;
}

// ?isPacketRouter@ConnectionManager@@QAE_NXZ
Bool ConnectionManager::isPacketRouter( void )
{
	return m_localSlot == m_packetRouterSlot;
}

// ?isPlayerConnected@ConnectionManager@@QAE_NH@Z
Bool ConnectionManager::isPlayerConnected( Int playerID )
{
	return ( playerID == m_localSlot || (m_connections[playerID] && m_connections[playerID]->m_openSentinel == -1) );
}
