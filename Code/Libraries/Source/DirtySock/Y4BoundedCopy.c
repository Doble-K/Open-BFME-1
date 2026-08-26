// cl: /Od /MD /DNDEBUG

void Rva0080D930( const char *source, int sourceLength,
	char *destination, int destinationLength )
{
	for ( ; sourceLength > 0 && destinationLength > 1;
		sourceLength--, destinationLength-- )
	{
		*destination = *source;
		destination++;
		source++;
	}

	if ( destinationLength > 0 )
	{
		*destination = 0;
	}
}
