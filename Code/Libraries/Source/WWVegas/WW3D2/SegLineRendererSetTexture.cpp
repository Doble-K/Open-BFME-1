// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class TextureClass
{
public:
	void Release_Ref();
};

class SegLineRendererClass
{
public:
	void Set_Texture(TextureClass *texture);

private:
	TextureClass *m_texture;
};

void SegLineRendererClass::Set_Texture(TextureClass *texture)
{
	TextureClass **next = reinterpret_cast<TextureClass **>(texture);
	if (*next)
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(*next) + 4);
	if (m_texture)
	{
		m_texture->Release_Ref();
		m_texture = *next;
	}
	else
	{
		m_texture = *next;
	}
}
