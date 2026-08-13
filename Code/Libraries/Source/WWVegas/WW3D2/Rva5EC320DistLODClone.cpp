class RenderObjClass
{
public:
	virtual ~RenderObjClass();
};

class DistLODClass : public RenderObjClass
{
public:
	DistLODClass(const DistLODClass &that);
	virtual RenderObjClass *Clone() const;

private:
	unsigned char m_data[168];
};

RenderObjClass *DistLODClass::Clone() const
{
	return new DistLODClass(*this);
}
