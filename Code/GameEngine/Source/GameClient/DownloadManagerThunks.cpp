class DownloadManager
{
public:
	virtual long OnError(int);
	virtual long OnStatusUpdate(int);
	long downloadNextQueuedFile();
};

__declspec(naked) long DownloadManager::OnError(int)
{
	__asm {
		_emit 0E9h
		_emit 0DAh
		_emit 04Eh
		_emit 05Fh
		_emit 000h
	}
}

__declspec(naked) long DownloadManager::OnStatusUpdate(int)
{
	__asm {
		_emit 0E9h
		_emit 058h
		_emit 0ECh
		_emit 061h
		_emit 000h
	}
}

__declspec(naked) long DownloadManager::downloadNextQueuedFile()
{
	__asm {
		_emit 0E9h
		_emit 06Bh
		_emit 0E4h
		_emit 05Eh
		_emit 000h
	}
}
