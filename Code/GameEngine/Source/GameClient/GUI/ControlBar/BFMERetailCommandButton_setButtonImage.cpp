// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringbaseascii /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
//
// BFMERetailCommandButton::setButtonImage, retail 0x0049C380. The class name is
// this tree's, from reloc_names.
//
// The images are a vector at +0x138. A button that already has one keeps the
// vector's length and just overwrites element zero; an empty one clears the
// count at +0x148 and appends, with retail inlining the whole push_back fast
// path and calling out only to _M_insert_overflow.
//
// The empty test is start against finish, not a size, which is why the two
// pointers are loaded before anything else happens.

#include "PreRTS.h"
#include "Common/STLTypedefs.h"

class Image;

class BFMERetailCommandButton
{
public:
	void setButtonImage( const Image *image );

private:
	unsigned char m_unmodelled_00[ 0x138 ];
	std::vector<const Image *> m_images;	// +0x138, twelve bytes
	unsigned char m_unmodelled_144[4];
	int m_unmodelled_148;					// +0x148
};

// ?setButtonImage@BFMERetailCommandButton@@QAEXPBVImage@@@Z
void BFMERetailCommandButton::setButtonImage( const Image *image )
{
	if( m_images.empty() )
	{
		m_unmodelled_148 = 0;
		m_images.push_back( image );
	}
	else
	{
		m_images[ 0 ] = image;
	}
}
