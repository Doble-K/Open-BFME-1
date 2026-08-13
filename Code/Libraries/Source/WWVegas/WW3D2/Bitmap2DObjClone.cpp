// cl: /DNDEBUG /MD /EHsc

class RenderObjClass
{
public:
	virtual ~RenderObjClass();
};

class Bitmap2DObjClass : public RenderObjClass
{
public:
	Bitmap2DObjClass(const Bitmap2DObjClass &that);
	virtual RenderObjClass *Clone() const;

private:
	unsigned char m_data[0x108];
};

RenderObjClass *Bitmap2DObjClass::Clone() const
{
	return new Bitmap2DObjClass(*this);
}
