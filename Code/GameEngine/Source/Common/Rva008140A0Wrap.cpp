// cl: /Od /GZ

struct Rva0081BD40Comm;

extern "C" int Rva0081BD40(struct Rva0081BD40Comm *comm, void *buffer, int size, unsigned int *when);

class Rva008140A0Obj
{
public:
	char m_lead[0x78];
	Rva0081BD40Comm *m_comm;
};

int Rva008140A0Wrap(Rva008140A0Obj *obj, void *buffer, int size, unsigned int *when)
{
	return Rva0081BD40(obj->m_comm, buffer, size, when);
}
