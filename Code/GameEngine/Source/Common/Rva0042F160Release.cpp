// cl: /O2 /Ob0

class UnicodeString
{
protected:
	void releaseBuffer();

	friend void __stdcall rva0042f160(UnicodeString other);
};

void __stdcall rva0042f160(UnicodeString other)
{
	other.releaseBuffer();
}
