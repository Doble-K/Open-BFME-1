// cl: /DNDEBUG /MD /GX- /O2 /Ob2

class TextureClass
{
public:
	void Release_Ref();
};

class PointGroupClass
{
public:
	void Set_Texture(TextureClass *texture);

private:
	char pad[0x24];
	TextureClass *Texture;
};

// ?Set_Texture@PointGroupClass@@QAEXPAVTextureClass@@@Z
void PointGroupClass::Set_Texture(TextureClass *texture)
{
	TextureClass **next = reinterpret_cast<TextureClass **>(texture);
	if (*next)
		++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(*next) + 4);
	if (Texture)
	{
		Texture->Release_Ref();
		Texture = *next;
	}
	else
	{
		Texture = *next;
	}
}
