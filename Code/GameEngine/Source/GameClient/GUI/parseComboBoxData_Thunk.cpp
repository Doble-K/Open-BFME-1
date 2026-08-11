// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift parseComboBoxData to clean C++.

#include <stdio.h>
#include <string.h>

typedef bool Bool;
typedef int Int;

class WinInstanceData;

struct ComboBoxData
{
	Bool isEditable;
	char m_pad[3];
	Int maxDisplay;
	Int maxChars;
	unsigned int flags;
};

static Int scanBool(const char *source, Bool &val)
{
	Int temp = 0;
	Int ret = sscanf(source, "%d", &temp);
	val = (Bool)temp;
	return ret;
}

static Int scanInt(const char *source, Int &val)
{
	return sscanf(source, "%d", &val);
}

// ?parseComboBoxData@@YA_NPADPAVWinInstanceData@@0PAX@Z
bool __cdecl parseComboBoxData(char *, WinInstanceData *, char *buffer, void *data)
{
	ComboBoxData *comboData = (ComboBoxData *)data;
	char *c;
	char *seps = " :,\n\r\t";

	c = strtok(buffer, seps);
	c = strtok(0, seps);
	scanBool(c, comboData->isEditable);

	c = strtok(0, seps);
	c = strtok(0, seps);
	scanInt(c, comboData->maxChars);

	c = strtok(0, seps);
	c = strtok(0, seps);
	scanInt(c, comboData->maxDisplay);

	comboData->flags = 0;
	c = strtok(0, seps);
	c = strtok(0, seps);
	Bool asciiOnly;
	scanBool(c, asciiOnly);
	if (asciiOnly)
		comboData->flags |= 0x10;

	c = strtok(0, seps);
	c = strtok(0, seps);
	Bool lettersAndNumbersOnly;
	scanBool(c, lettersAndNumbersOnly);
	if (lettersAndNumbersOnly)
		comboData->flags |= 0x40;

	return true;
}
