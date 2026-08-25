// cl: /O2 /Ob0

class Rva007B13D0G
{
public:
	void bar(void *);
};

Rva007B13D0G *g_rva007b13d0;

class Rva007B13D0
{
public:
	void run();
};

void Rva007B13D0::run()
{
	g_rva007b13d0->bar(this);
}
