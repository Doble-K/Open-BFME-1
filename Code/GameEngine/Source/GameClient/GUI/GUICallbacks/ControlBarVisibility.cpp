// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/scriptenginelayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "Common/NameKeyGenerator.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/ControlBar.h"
#include "GameClient/GameWindow.h"
#include "GameClient/GameWindowManager.h"

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }
	const char *str() const
	{
		static const char empty = 0;
		return m_data ? m_data + 8 : &empty;
	}

private:
	void releaseBuffer();
	char *m_data;
};

class BFMEWindowManagerVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual GameWindow *winGetWindowFromId( GameWindow *parent, int id ) = 0;
};

class BFMEViewVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void setHeight( int height ) = 0;
};

class BFMEDisplayVTable
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual void slot8() = 0;
	virtual void slot9() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual int getHeight() = 0;
};

class AptPalantir
{
public:
	void hide( bool immediate );
};

class BannerUI
{
public:
	void hide( bool immediate );
};

extern void hideReplayControls();
extern ControlBar *TheControlBar;
extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern void *TheTacticalView;
extern void *TheDisplay;
extern AptPalantir *TheAptPalantir;
extern BannerUI *TheBannerUI;

void HideControlBar( bool immediate )
{
	hideReplayControls();
	if( TheControlBar )
		TheControlBar->hideSpecialPowerShortcut();

	if( TheWindowManager )
	{
		int id;
		{
			BFMERetailAsciiString name( "ControlBar.wnd:ControlBarParent" );
			id = TheNameKeyGenerator->nameToKey( name.str() );
		}
		GameWindow *window = reinterpret_cast<BFMEWindowManagerVTable *>( TheWindowManager )->winGetWindowFromId( 0, id );
		if( window )
		{
			reinterpret_cast<BFMEViewVTable *>( TheTacticalView )->setHeight(
				reinterpret_cast<BFMEDisplayVTable *>( TheDisplay )->getHeight() );
		}

		if( immediate )
		{
			if( window )
				window->winHide( true );
			if( TheControlBar )
				TheControlBar->hideSpecialPowerShortcut();
		}
		else if( TheControlBar )
		{
			if( TheControlBar->m_animateWindowManager )
				TheControlBar->m_animateWindowManager->reverseAnimateWindow();
			TheControlBar->animateSpecialPowerShortcut( false );
		}

		if( TheControlBar )
			TheControlBar->hidePurchaseScience();
	}

	if( TheAptPalantir )
		TheAptPalantir->hide( true );
	if( TheBannerUI )
		TheBannerUI->hide( true );
}
