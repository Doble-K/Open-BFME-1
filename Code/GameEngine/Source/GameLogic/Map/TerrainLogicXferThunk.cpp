// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: TerrainLogic::xfer, retail 0x006BE430, 45 bytes.
//
// The Zero Hour prologue: a version pair is built on the stack -- both bytes
// written from one materialised 1, which is what `const XferVersion
// currentVersion = 1; XferVersion version = currentVersion;` compiles to --
// handed to Xfer's vftable slot 0x28, and then the rest of the transfer is a
// single call into the body at 0x001AD370 (ILT 0x00043ED7).

class Xfer;

struct TerrainLogicXferVersion
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class Xfer
{
public:
	virtual void xferSlot00();
	virtual void xferSlot04();
	virtual void xferSlot08();
	virtual void xferSlot0c();
	virtual void xferSlot10();
	virtual void xferSlot14();
	virtual void xferSlot18();
	virtual void xferSlot1c();
	virtual void xferSlot20();
	virtual void xferSlot24();
	virtual void xferVersion(TerrainLogicXferVersion *versionData);
};

class TerrainLogic
{
protected:
	virtual void xfer(Xfer *xfer);
	void xferTerrainState(Xfer *xfer);
};

// ?xfer@TerrainLogic@@MAEXPAVXfer@@@Z
void TerrainLogic::xfer(Xfer *xfer)
{
	const unsigned char currentVersion = 1;
	TerrainLogicXferVersion version;

	version.m_version = currentVersion;
	version.m_currentVersion = currentVersion;
	xfer->xferVersion(&version);

	xferTerrainState(xfer);
}
