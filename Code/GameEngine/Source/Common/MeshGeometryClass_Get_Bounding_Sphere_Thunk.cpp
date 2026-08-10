// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the MeshGeometryClass::Get_Bounding_Sphere naked dump to clean C++.
//
// The retail body is a straight copy of the two bound fields into the output
// SphereClass: BoundSphereCenter at this+0x80 (Vector3) and BoundSphereRadius
// at this+0x8C, landing at SphereClass.Center (+0x00) and .Radius (+0x0C).
//
// The reference WWMath Vector3 is replicated (not hand-rolled) so the copy
// constructor shape matches the sibling Get_Bounding_Box conversion.

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3(void) {};
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }

	Vector3 &operator = (const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
};

class SphereClass
{
public:
	Vector3 Center;		///< retail this+0x00
	float Radius;		///< retail this+0x0C
};

class MeshGeometryClass
{
public:
	void Get_Bounding_Sphere(SphereClass *set_sphere);

private:
	unsigned char m_unreconstructed_00[0x80];
	Vector3 BoundSphereCenter;	///< retail this+0x80
	float BoundSphereRadius;	///< retail this+0x8C
};

// ?Get_Bounding_Sphere@MeshGeometryClass@@QAEXPAVSphereClass@@@Z
void MeshGeometryClass::Get_Bounding_Sphere(SphereClass *set_sphere)
{
	set_sphere->Center = BoundSphereCenter;
	set_sphere->Radius = BoundSphereRadius;
}
