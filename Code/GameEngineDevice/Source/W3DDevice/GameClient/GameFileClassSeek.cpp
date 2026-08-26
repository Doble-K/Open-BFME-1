// cl: /DNDEBUG /MD /EHsc

class File
{
public:
	enum seekMode
	{
		START,
		CURRENT,
		END
	};

	virtual ~File();
	virtual int open(const char *filename, int access);
	virtual void close();
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, seekMode mode);
};

class GameFileClass
{
public:
	virtual int Seek(int position, int direction);

private:
	File *m_file;
};

int GameFileClass::Seek(int position, int direction)
{
	File::seekMode mode = File::CURRENT;
	switch (direction) {
	default:
	case 1:
		mode = File::CURRENT;
		break;
	case 0:
		mode = File::START;
		break;
	case 2:
		mode = File::END;
		break;
	}
	if (m_file) {
		return m_file->seek(position, mode);
	}
	return -1;
}
