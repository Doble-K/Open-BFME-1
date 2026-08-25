// cl: /Od /GZ

struct Rva0081BD40Comm;

extern "C" int Rva0081BA60(struct Rva0081BD40Comm *comm, const void *payload, int length);

class Rva00814040Obj
{
public:
	char m_lead[0x78];
	Rva0081BD40Comm *m_comm;
};

int Rva00814040Wrap(Rva00814040Obj *obj, const void *payload, int length)
{
	return Rva0081BA60(obj->m_comm, payload, length);
}
