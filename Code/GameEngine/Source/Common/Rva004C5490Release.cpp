// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class WindowLayout;

void ReleaseWindowLayout(WindowLayout *layout);

void Rva004C5490()
{
	ReleaseWindowLayout(0);
}
