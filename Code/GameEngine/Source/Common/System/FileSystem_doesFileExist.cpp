// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// IAT form of sprintf: call dword ptr [__imp__sprintf]
extern "C" int (__cdecl *__imp__sprintf)(char *, const char *, ...);
static inline int do_sprintf(char *b, const char *f, const char *a, const char *c)
{
	return (*__imp__sprintf)(b, f, a, c);
}

class LocalFileSystem {
public:
	virtual ~LocalFileSystem() {}
	virtual void L1() = 0;
	virtual void L2() = 0;
	virtual void L3() = 0;
	virtual void L4() = 0;
	virtual void L5() = 0;
	virtual void L6() = 0;
	virtual void L7() = 0;
	// slot 8 = +0x20
	virtual bool doesFileExist(const char *filename) const = 0;
};

class ArchiveFileSystem {
public:
	virtual ~ArchiveFileSystem() {}
	virtual void A1() = 0;
	virtual void A2() = 0;
	virtual void A3() = 0;
	// slot 4 = +0x10
	virtual bool doesFileExist(const char *filename) const = 0;
};

extern LocalFileSystem *TheLocalFileSystem;
extern ArchiveFileSystem *TheArchiveFileSystem;
// retail global path prefix used by sprintf("%s\\%s", prefix, filename)
extern char byte_134CA48[];

class FileSystem {
public:
	bool doesFileExist(const char *filename) const;
};

// ?doesFileExist@FileSystem@@QBE_NPBD@Z
bool FileSystem::doesFileExist(const char *filename) const
{
	char buf[0x200];
	do_sprintf(buf, "%s\\%s", byte_134CA48, filename);
	if (TheLocalFileSystem->doesFileExist(buf))
		return true;
	if (TheLocalFileSystem->doesFileExist(filename))
		return true;
	if (TheArchiveFileSystem->doesFileExist(buf))
		return true;
	if (TheArchiveFileSystem->doesFileExist(filename))
		return true;
	return false;
}
