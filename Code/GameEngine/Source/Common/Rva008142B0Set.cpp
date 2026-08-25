// cl: /Od

class Rva008142B0Obj
{
public:
	char m_lead[0x48];
	int m_at48;
	char m_mid[0x7C - 0x48 - 4];
	int m_at7C;
};

void Rva008142B0Set(Rva008142B0Obj *obj, int value)
{
	obj->m_at7C = value;
	obj->m_at48 = value;
}
