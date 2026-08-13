// cl: /DNDEBUG /MD /EHsc

class RecorderClass
{
public:
	RecorderClass();

private:
	unsigned char m_data[0x2b4];
};

RecorderClass *createRecorder()
{
	return new RecorderClass;
}
