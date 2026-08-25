// cl: /O2 /Ob0

class UnicodeString
{
protected:
	void releaseBuffer();

	friend void __stdcall rva00558d90(int, UnicodeString);
};

void __stdcall rva00558d90(int, UnicodeString other)
{
	other.releaseBuffer();
}
