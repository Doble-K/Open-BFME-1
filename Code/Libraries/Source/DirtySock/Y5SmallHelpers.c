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
