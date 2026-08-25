// cl: /Od /GZ /MD /DNDEBUG

void *memcpy(void *dest, const void *src, unsigned int count);

int Rva008118D0(void)
{
	return -1;
}

int Rva008118F0(void)
{
	return -1;
}

int Rva0080E330(void *crypto, int length)
{
	if (*(int *)crypto != 0)
		length += 8;
	return length;
}

int Rva0080E300(const int *crypto, int length)
{
	if (crypto[0] != 0 && crypto[1] != 0 && length >= 8)
		length -= 8;
	return length;
}

void Rva0080F300(void *state, unsigned char *data, int length);
void Rva0080F200(void *state, const unsigned char *key, int length, int rounds);
void Rva0080E500(void *object);
void Rva007F0030(void *object);

void Rva0080E410(void *crypto, unsigned char *data, int length)
{
	if (*(int *)crypto != 0)
		Rva0080F300((unsigned char *)crypto + 0x10A, data, length);
}

void Rva0080E1C0(int *crypto, unsigned char *data, int length)
{
	if (crypto[0] != 0)
	{
		Rva0080F300((unsigned char *)crypto + 8, data, length);
		crypto[1] = 1;
	}
}

int Rva0080DFC0(int *crypto, const unsigned char *key)
{
	crypto[0] = 0;
	if (key != 0)
	{
		crypto[0] = 1;
		crypto[1] = 0;
		Rva0080F200((unsigned char *)crypto + 0x10A, key, 0x10, -1);
		Rva0080F200((unsigned char *)crypto + 8, key + 0x10, 0x10, -1);
	}
	return crypto[0];
}

void Rva0080F530(void *dest, const void *src, int length)
{
	memcpy(dest, src, length);
}

void Rva0080F3D0(unsigned char *state, const void *first, int firstLength,
	const void *second, int secondLength)
{
	*(int *)(state + 0x400) = firstLength;
	*(int *)(state + 0x488) = secondLength;
	memcpy(state + 0x404, first, firstLength);
	memcpy(state + 0x48C, second, secondLength);
}

int Rva0080DF70(const unsigned char *source, void *first, void *second)
{
	if (first != 0)
		memcpy(first, source, 0x20);
	if (second != 0)
		memcpy(second, source + 0x20, 0x34);
	return 1;
}

int Rva0080DC90(const unsigned char *first, const void *second,
	unsigned char *combined)
{
	memcpy(combined, first, 0x20);
	memcpy(combined + 0x20, second, 0x10);
	memcpy(combined + 0x30, first, 0x20);
	return 0x50;
}

void Rva0080E4D0(void *object)
{
	Rva0080E500(object);
	Rva007F0030(object);
}
