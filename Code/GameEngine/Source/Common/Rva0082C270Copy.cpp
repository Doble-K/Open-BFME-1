// cl: /Od /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class Rva0082C270Copy
{
public:
	int *copyTo(int *out);

private:
	int m_pad;
	int m_value;
};

int *Rva0082C270Copy::copyTo(int *out)
{
	int temp = m_value;
	*out = temp;
	return out;
}
