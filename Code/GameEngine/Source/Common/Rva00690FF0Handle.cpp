// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Gen0002857E
{
public:
	void handle();
};

class Rva00690FF0Handle
{
public:
	Rva00690FF0Handle(Gen0002857E *target);

	Gen0002857E *m_target;
};

Rva00690FF0Handle::Rva00690FF0Handle(Gen0002857E *target)
{
	m_target = target;
	if (target)
		target->handle();
}
