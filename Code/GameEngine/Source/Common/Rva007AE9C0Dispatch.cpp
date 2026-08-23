// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;

class Rva007AE9C0Dispatcher
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void dispatch( UnsignedInt first, UnsignedInt mode,
		UnsignedInt second, UnsignedInt third );

	void forward( UnsignedInt first, UnsignedInt second, UnsignedInt third );
};

void Rva007AE9C0Dispatcher::forward( UnsignedInt first, UnsignedInt second,
	UnsignedInt third )
{
	dispatch( first, 0, second, third );
}
