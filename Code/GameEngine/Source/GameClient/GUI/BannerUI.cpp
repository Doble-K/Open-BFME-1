// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The BannerUI block -- BFME's unit banners, which Zero Hour has no equivalent
// for. One global settings object, parsed straight into.
//
// Several names here are ours rather than retail's, and it is worth being
// explicit about which. The block keyword "BannerUI" comes from the registry,
// so the settings class is named. The pointer at 0x012F4B70 is not: nothing in
// the image names it, and the only matched rows that touch it are InGameUI's
// constructor, destructor and update, which say where it is owned but not what
// it is called. The parser name follows the keyword. The callback at 0x00582C70
// is installed by BannerUI's selected-entry routine at 0x00583190, and its
// current-id global and removal member are likewise unnamed, so their names
// below describe that proven ownership and behavior rather than claiming a
// recovered retail spelling.
#include "PreRTS.h"
#include "Common/INI.h"
#include <algorithm>
#include <vector>

struct BannerMovieEntry
{
	int m_unmodelled;
	int m_id;
	unsigned char m_unmodelled_08[ 20 ];
};

class BannerMovieEntryMatches
{
public:
	BannerMovieEntryMatches( int id ) : m_id( id ) {}
	bool operator()( const BannerMovieEntry &entry ) const { return entry.m_id == m_id; }

private:
	int m_id;
};

class BannerUI
{
public:
	static const FieldParse m_fieldParseTable[];
	virtual void reset();
	void removeMovieBanner( int id );
	void removeCurrentBannerMovie();
	void hide( bool immediate );

private:
	unsigned char m_unmodelled[ 0x28 ];
	int m_windowIndex;
	std::vector<BannerMovieEntry> m_movieEntries;
	bool m_hidden;
};

extern BannerUI *TheBannerUI;

class BfmeDisplayMovie
{
public:
	#define BFME_DISPLAY_SLOT( n ) virtual void bfmeDisplaySlot##n() = 0
	BFME_DISPLAY_SLOT( 0 ); BFME_DISPLAY_SLOT( 1 ); BFME_DISPLAY_SLOT( 2 );
	BFME_DISPLAY_SLOT( 3 ); BFME_DISPLAY_SLOT( 4 ); BFME_DISPLAY_SLOT( 5 );
	BFME_DISPLAY_SLOT( 6 ); BFME_DISPLAY_SLOT( 7 ); BFME_DISPLAY_SLOT( 8 );
	BFME_DISPLAY_SLOT( 9 ); BFME_DISPLAY_SLOT( 10 ); BFME_DISPLAY_SLOT( 11 );
	BFME_DISPLAY_SLOT( 12 ); BFME_DISPLAY_SLOT( 13 ); BFME_DISPLAY_SLOT( 14 );
	BFME_DISPLAY_SLOT( 15 ); BFME_DISPLAY_SLOT( 16 ); BFME_DISPLAY_SLOT( 17 );
	BFME_DISPLAY_SLOT( 18 ); BFME_DISPLAY_SLOT( 19 ); BFME_DISPLAY_SLOT( 20 );
	BFME_DISPLAY_SLOT( 21 ); BFME_DISPLAY_SLOT( 22 ); BFME_DISPLAY_SLOT( 23 );
	BFME_DISPLAY_SLOT( 24 ); BFME_DISPLAY_SLOT( 25 ); BFME_DISPLAY_SLOT( 26 );
	BFME_DISPLAY_SLOT( 27 ); BFME_DISPLAY_SLOT( 28 ); BFME_DISPLAY_SLOT( 29 );
	BFME_DISPLAY_SLOT( 30 ); BFME_DISPLAY_SLOT( 31 ); BFME_DISPLAY_SLOT( 32 );
	BFME_DISPLAY_SLOT( 33 ); BFME_DISPLAY_SLOT( 34 ); BFME_DISPLAY_SLOT( 35 );
	BFME_DISPLAY_SLOT( 36 ); BFME_DISPLAY_SLOT( 37 ); BFME_DISPLAY_SLOT( 38 );
	BFME_DISPLAY_SLOT( 39 ); BFME_DISPLAY_SLOT( 40 ); BFME_DISPLAY_SLOT( 41 );
	BFME_DISPLAY_SLOT( 42 ); BFME_DISPLAY_SLOT( 43 ); BFME_DISPLAY_SLOT( 44 );
	BFME_DISPLAY_SLOT( 45 ); BFME_DISPLAY_SLOT( 46 ); BFME_DISPLAY_SLOT( 47 );
	BFME_DISPLAY_SLOT( 48 ); BFME_DISPLAY_SLOT( 49 ); BFME_DISPLAY_SLOT( 50 );
	BFME_DISPLAY_SLOT( 51 ); BFME_DISPLAY_SLOT( 52 ); BFME_DISPLAY_SLOT( 53 );
	BFME_DISPLAY_SLOT( 54 ); BFME_DISPLAY_SLOT( 55 ); BFME_DISPLAY_SLOT( 56 );
	BFME_DISPLAY_SLOT( 57 ); BFME_DISPLAY_SLOT( 58 );
	#undef BFME_DISPLAY_SLOT
	virtual void stopMovie() = 0;
	virtual bool isMoviePlaying() = 0;
	virtual void bfmeDisplaySlot61() = 0;
	virtual bool bfmeMovieState() = 0;
};

class Display;
class GlobalData;

struct BfmeGlobalDataMovieState
{
	unsigned char m_unmodelled[ 0xA7D ];
	bool m_allowMovieExit;
};

extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
extern int TheCurrentBannerMovie;

class WindowManager
{
public:
	bool hideAptWindow( int index );
	bool showAptWindow( int index );
};

extern WindowManager *g_theWindowManager;
extern void DeleteBanner( int id );

void parseBannerUI( INI *ini )
{
	ini->initFromINI( TheBannerUI, BannerUI::m_fieldParseTable );
}

int finishBannerMovie()
{
	int result = 0;

	if( !reinterpret_cast<BfmeDisplayMovie *>( TheDisplay )->isMoviePlaying() ||
		reinterpret_cast<BfmeDisplayMovie *>( TheDisplay )->bfmeMovieState() ||
		reinterpret_cast<BfmeGlobalDataMovieState *>( TheWritableGlobalData )->m_allowMovieExit )
	{
		if( TheCurrentBannerMovie != -1 )
		{
			int id = TheCurrentBannerMovie;
			TheCurrentBannerMovie = -1;
			TheBannerUI->removeMovieBanner( id );
		}

		reinterpret_cast<BfmeDisplayMovie *>( TheDisplay )->stopMovie();
		result = 2;
	}

	return result;
}

void BannerUI::removeCurrentBannerMovie()
{
	if( TheCurrentBannerMovie != -1 )
	{
		int id = TheCurrentBannerMovie;
		TheCurrentBannerMovie = -1;
		removeMovieBanner( id );
	}
}

void BannerUI::removeMovieBanner( int id )
{
	if( TheCurrentBannerMovie == id )
		return;

	std::vector<BannerMovieEntry>::iterator entry =
		std::find_if( m_movieEntries.begin(), m_movieEntries.end(), BannerMovieEntryMatches( id ) );
	if( entry != m_movieEntries.end() )
	{
		DeleteBanner( id );
		m_movieEntries.erase( entry );
	}
}

void BannerUI::hide( bool immediate )
{
	if( g_theWindowManager )
	{
		m_hidden = immediate;
		if( immediate )
		{
			g_theWindowManager->hideAptWindow( m_windowIndex );
			m_movieEntries.clear();
		}
		else
		{
			g_theWindowManager->showAptWindow( m_windowIndex );
		}
	}
}

void BannerUI::reset()
{
	hide( true );
	m_movieEntries.clear();
}

template void std::vector<BannerMovieEntry>::push_back( const BannerMovieEntry &entry );
