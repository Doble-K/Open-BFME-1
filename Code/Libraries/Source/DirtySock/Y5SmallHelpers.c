// cl: /Od /GZ /MD /DNDEBUG

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

void Rva0080E410(void *crypto, unsigned char *data, int length)
{
	if (*(int *)crypto != 0)
		Rva0080F300((unsigned char *)crypto + 0x10A, data, length);
}
