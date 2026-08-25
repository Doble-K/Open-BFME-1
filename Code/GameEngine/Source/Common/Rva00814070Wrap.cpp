// cl: /Od /GZ

struct Rva0081BD40Comm;

extern "C" int Rva0081BC80(struct Rva0081BD40Comm *comm, void *buffer, int size, unsigned int *when);

class Rva00814070Obj
{
public:
	char m_lead[0x78];
	Rva0081BD40Comm *m_comm;
};

int Rva00814070Wrap(Rva00814070Obj *obj, void *buffer, int size, unsigned int *when)
{
	return Rva0081BC80(obj->m_comm, buffer, size, when);
}
