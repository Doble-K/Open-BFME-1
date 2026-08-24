class Rva00588760Object
{
public:
	Rva00588760Object *clearByte();

private:
	unsigned char m_flag;
};

Rva00588760Object *Rva00588760Object::clearByte()
{
	m_flag = 0;
	return this;
}
