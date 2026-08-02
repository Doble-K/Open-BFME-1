// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Grok promote from masm_dumps — retail 0x007105D0 size 61
// was: Code/masm_dumps/W3DRoadBuffer_loadRoads.asm

class W3DRoadBuffer {
public:
	void loadRoadsHelper0(void);
	void loadRoadsHelper1(void);
	void loadRoadsHelper2(void);
	static void loadRoadsHelper3(void);
	void loadRoadsHelper4(void);
	void loadRoadsHelper5(void);
	void loadRoadsHelper6(void);
	void loadRoads(void);
};

// ?loadRoads@W3DRoadBuffer@@QAEXXZ
void W3DRoadBuffer::loadRoads(void)
{
	if (*(unsigned char *)((unsigned char *)this + 0x0C))
	{
		loadRoadsHelper0();
		loadRoadsHelper1();
		loadRoadsHelper2();
		loadRoadsHelper3();
		loadRoadsHelper4();
		loadRoadsHelper5();
		loadRoadsHelper6();
		*(unsigned char *)((unsigned char *)this + 0x50) = 1;
	}
}

