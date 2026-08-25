// ?func0073B540@@YGXHH@Z
// partial score=0.9 date=2026-08-25

struct Vec3 { int x, y, z; };
extern Vec3 g_vec1;
extern Vec3 g_vec2;
extern Vec3 g_vec3;
extern int g_flag1;
extern bool g_flag2;

void __stdcall func0073B540( int y, int x )
{
	g_vec1.x = x;
	g_vec1.y = y;
	g_vec1.z = 0;

	g_vec2.x = x;
	g_vec2.y = 12;
	g_vec2.z = 0;
	
	g_flag1 = 1;
	g_flag2 = 0;

	g_vec3.x = x;
	g_vec3.y = y;
	g_vec3.z = 0;
}
