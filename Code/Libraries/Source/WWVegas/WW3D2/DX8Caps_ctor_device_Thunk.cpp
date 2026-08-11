// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Open-BFME5: lift the device-backed DX8 capability constructor to clean C++.

#include "wwstring.h"

struct IDirect3D8;
struct IDirect3DDevice8;
struct _D3DADAPTER_IDENTIFIER8;
enum WW3DFormat { WW3DFormat_dummy = 0 };

class DX8Caps
{
public:
	DX8Caps(IDirect3D8 *, IDirect3DDevice8 *, WW3DFormat,
		const _D3DADAPTER_IDENTIFIER8 &);

private:
	void Init_Caps(IDirect3DDevice8 *);
	void Compute_Caps(WW3DFormat, const _D3DADAPTER_IDENTIFIER8 &);

	int m_maxDisplayWidth;
	int m_maxDisplayHeight;
	unsigned char m_unreconstructed_008[0x284];
	int m_vendorId;
	unsigned char m_unreconstructed_290[0x0C];
	StringClass m_driverDLL;
	IDirect3D8 *m_direct3D;
	StringClass m_capsLog;
	StringClass m_compactLog;
};

// ??0DX8Caps@@QAE@PAUIDirect3D8@@PAUIDirect3DDevice8@@W4WW3DFormat@@ABU_D3DADAPTER_IDENTIFIER8@@@Z
DX8Caps::DX8Caps(IDirect3D8 *direct3D, IDirect3DDevice8 *device,
	WW3DFormat displayFormat, const _D3DADAPTER_IDENTIFIER8 &adapterIdentifier)
	: m_maxDisplayWidth(0),
	  m_maxDisplayHeight(0),
	  m_vendorId(0),
	  m_direct3D(direct3D)
{
	Init_Caps(device);
	Compute_Caps(displayFormat, adapterIdentifier);
}
