// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistringsetoutofline /Ireference/shims/psplayerstats /Ireference/shims/peerdefs /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: lift GameSpyInfo::leaveGroupRoom to clean C++.

#define Matrix4x4 Matrix4
class INI;
#include "GameNetwork/GameSpy/PeerDefsImplementation.h"
#include "GameNetwork/GameSpy/PeerThread.h"

class BFMEGroupRoomInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void setCurrentGroupRoom(Int groupID);
	virtual Int getCurrentGroupRoom();
};

struct BFMERetailPeerRequest
{
	PeerRequest request;
	unsigned char m_tailPad[4];
};

// ?leaveGroupRoom@GameSpyInfo@@UAEXXZ
void GameSpyInfo::leaveGroupRoom(void)
{
	BFMERetailPeerRequest retailRequest;
	PeerRequest &request = retailRequest.request;
	request.peerRequestType = PeerRequest::PEERREQUEST_LEAVEGROUPROOM;
	BFMEGroupRoomInterface *roomInterface = (BFMEGroupRoomInterface *)this;
	request.groupRoom.id = roomInterface->getCurrentGroupRoom();
	TheGameSpyPeerMessageQueue->addRequest(request);
	roomInterface->setCurrentGroupRoom(0);
	m_playerInfoMap.clear();
}
