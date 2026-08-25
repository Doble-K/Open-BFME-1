// ?_bfme_debugRecordCallsite@@YAXH@Z
// partial score=0.95 date=2026-08-25
// cl: /DNDEBUG /MD /EHs-c- /Oy-

extern "C" void * _ReturnAddress(void);
#pragma intrinsic(_ReturnAddress)

class Gen001336E5C
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C( void *retAddr, int kind );
};

extern Gen001336E5C *TheGen001336E5C;

// ?_bfme_debugRecordCallsite@@YAXH@Z @ 0x008896A0
void _bfme_debugRecordCallsite( int kind )
{
	void * volatile retAddr = _ReturnAddress();
	TheGen001336E5C->slot5C( retAddr, kind );
}
