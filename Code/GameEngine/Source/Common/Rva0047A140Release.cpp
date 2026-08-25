// cl: /O2 /Ob0

class UnicodeString
{
protected:
	void releaseBuffer();

	friend void __stdcall rva0047a140(int, UnicodeString, int, int, int, int, int);
};

void __stdcall rva0047a140(int, UnicodeString other, int, int, int, int, int)
{
	other.releaseBuffer();
}
