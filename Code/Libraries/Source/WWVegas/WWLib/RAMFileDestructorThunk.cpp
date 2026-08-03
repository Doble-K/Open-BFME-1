// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift RAMFile dtor __emit thunk to clean C++. Retail stores its
// own vtable, operator-deletes the buffer member at this+0x14, calls
// File::close() on this (virtual, resolved directly in dtor context), then
// drops EH state to -1 and calls the out-of-line File dtor.

class File
{
public:
    virtual ~File();
    virtual void close();

private:
    unsigned char m_pad[0x10];
};

class RAMFile : public File
{
protected:
    virtual ~RAMFile();

private:
    char *m_buffer;
};

// ??1RAMFile@@MAE@XZ
RAMFile::~RAMFile()
{
    delete m_buffer;
    close();
}
