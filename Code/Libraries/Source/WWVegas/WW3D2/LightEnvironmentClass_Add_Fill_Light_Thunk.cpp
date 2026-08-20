// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Lift LightEnvironmentClass::Add_Fill_Light (0x94ACB0) to clean C++.
//
// Local ABI-slice replica.  The body is Zero Hour's verbatim; the only thing
// that was ever wrong was the layout.  Retail reads LightCount at this+0x04
// (mov eax,[ecx+4] -- a three-byte form, which is the whole 207-vs-205 size
// gap) and every float field sits exactly four bytes above where the Zero Hour
// header puts it: OutputAmbient at +0x164, FillLight at +0x1d0, FillLight's
// Ambient at +0x1dc and Diffuse at +0x1e8, InputLights based at +0x14.
// One BFME-only dword ahead of LightCount accounts for all of it -- the same
// shape as MeshGeometryClass, whose copy constructor landed this session with
// its own leading BFME member.

#include "always.h"
#include "vector3.h"

class LightClass;
class Matrix3D;

class LightEnvironmentClass
{
public:
	void					Add_Fill_Light(void);

	enum { MAX_LIGHTS = 4 };

protected:

	struct InputLightStruct
	{
		Vector3			Direction;
		Vector3			Ambient;
		Vector3			Diffuse;
		bool				DiffuseRejected;

		bool				m_point;
		Vector3			m_center;
		float				m_innerRadius;
		float				m_outerRadius;
		Vector3			m_ambient;
		Vector3			m_diffuse;
	};

	struct OutputLightStruct
	{
		Vector3			Direction;
		Vector3			Diffuse;
	};

	int					_bfme_lightenv_v0;			///< retail this+0x00
	int					LightCount;						///< retail this+0x04
	Vector3				ObjectCenter;					///< retail this+0x08
	InputLightStruct	InputLights[MAX_LIGHTS];	///< retail this+0x14
	Vector3				OutputAmbient;					///< retail this+0x164
	OutputLightStruct	OutputLights[MAX_LIGHTS];	///< retail this+0x170
	InputLightStruct 	FillLight;						///< retail this+0x1d0
	float					FillIntensity;					///< retail this+0x224
};

// ?Add_Fill_Light@LightEnvironmentClass@@QAEXXZ
void LightEnvironmentClass::Add_Fill_Light(void)
{
	// Don't add black (or almost black) lights!
	if (FillLight.Diffuse[0]<0.05f && FillLight.Diffuse[1]<0.05f && FillLight.Diffuse[2]<0.05f) {
		OutputAmbient += FillLight.Ambient;
		return;
	}

	// Get the 1st empty light slot or the very last slot regardless of whether the last slot is empty or not
	int slot = 0;
	if (LightCount == MAX_LIGHTS) {
		slot = MAX_LIGHTS - 1;
	} else {
		slot = LightCount;
		++LightCount;
	}

	/*
	** Add in the ambient component
	*/
	OutputAmbient += FillLight.Ambient;

	/*
	** Insert the fill light into the calculated slot of the InputLights
	*/
	InputLights[slot] = FillLight;
}
