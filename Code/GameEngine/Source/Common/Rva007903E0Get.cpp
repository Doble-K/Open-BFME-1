// cl: /O2 /Ob0

class GameWindow
{
public:
	void *winGetUserData(void);
};

struct Rva007903E0User
{
	char m_lead[4];
	void *m_field;
};

class Rva007903E0
{
	GameWindow *m_window;

public:
	void *get();
};

void *Rva007903E0::get()
{
	return ((Rva007903E0User *)m_window->winGetUserData())->m_field;
}
